import os
from Constants import Constants
from Request import Request
from Response import Response
from SocketHandler import SocketHandler

def stopClient(err):  
    print("\nError:Fatal Error!", err, "Script execution will stop.", sep="\n")
    exit(1)

# parse server info . 
# return IP String, port. 
# Stop script if error occurred
def parseServerInfo(server_info):
    try:
        with open(server_info, "r") as info:
         values = info.readline().strip().split(":")        
        return values[0], int(values[1])
    except Exception as ex:
        stopClient(f"Error:parseServerInfo Exception: {ex}!")


# parse backup info for files list. 
# Stop script on failure 
def parseFileList(backupInfo):
    try:
        with open(backupInfo, "r") as info:
            filesList = [line.strip() for line in info]
            for fileName in filesList:
                if len(fileName) > Constants.MAX_NAME_LEN:                    
                    stopClient(f"Error:file name exceeding length {Constants.MAX_NAME_LEN} was found in {backupInfo}!")
                if len(filesList) < 2:                    
                    stopClient(f"Error:there must be least two files in {backupInfo}!")         
            return filesList
    except Exception as ex:
        stopClient(f"Error:parseFileList Exception: {ex}!")

#Send a request for file list from server
def requestFilesList():
    try:
        request = request.getRequest(request.EOp.FILE_DIR)
        with request.initializeSocket() as socket:
            request.socketSend(socket, request.pack())
            response = response(socket.recv(Constants.PACKET_SIZE))
            if response.validate(response.EStatus.SUCCESS_DIR):
                bytesRead = len(response.payload.payload)
                buffer = response.payload.payload
                while bytesRead < response.payload.size:
                    buffer = buffer + socket.recv(Constants.PACKET_SIZE)                
            #split by \n and remove empty entries
            files = [file.strip() for file in buffer.decode('utf-8').split('\n')].remove("")
            if files:
                print(f"Received file list, status code {response.status}:")
                for file in files:
                    print(f"\t{file}")
                else:
                    print(f"Error:Invalid response: status code {response.status}. file list is empty!")
    except Exception as ex:
        stopClient(f"Error:requestFilesList Exception: {ex}!")

#Request to backup a file to the server
def requestFileBackup(fileName):
    try:
        request = request.getRequest(request.EOp.FILE_BACKUP, fileName)
        request.payload.size = os.path.getsize(fileName)
        with open(fileName, "rb") as file: # read binary
            request.payload.payload = file.read(Constants.PACKET_SIZE - request.sizeWithoutPayload())
            with request.initializeSocket() as socket:
                request.socketSend(socket, request.pack())
                payload = file.read(Constants.PACKET_SIZE)
                while payload:
                    SocketHandler.sendSocket(socket, payload)
                    payload = file.read(Constants.PACKET_SIZE)      
                response = response(socket.recv(Constants.PACKET_SIZE))
        if response.validate(response.EStatus.SUCCESS_BACKUP_REMOVE):
            print(f"File '{fileName}' successfully backed-up. status code {response.status}.")
    except Exception as ex:
        stopClient(f"Error: requestFileBackup Exception: {ex}!")

# request to restore a file from the server
def requestFileRestore(filename, restoreTo=""):
    try:
        request = request.getRequest(request.EOp.FILE_RESTORE, filename)
        with request.initializeSocket() as socket:
            request.socketSend(socket, request.pack())
            response = response(socket.recv(Constants.PACKET_SIZE))
            if response.validate(response.EStatus.SUCCESS_RESTORE):
                if restoreTo is None:
                    restore_to = response.fileName
                if response.fileName is None:
                    print(f"Error: Restore Error. Invalid filename. status code {response.status}.")
                else:
                    file = open(restoreTo, "wb")#write binary
                    bytesRead = len(response.payload.payload)
                    file.write(response.payload.payload)
                    while bytesRead < response.payload.size:
                        data = socket.recv(Constants.PACKET_SIZE)
                        dataLen = len(data)
                        if dataLen + bytesRead > response.payload.size:
                            dataLen = response.payload.size - bytesRead
                        file.write(data[:dataLen])
                        bytesRead += dataLen
        print(f"File '{response.filename}' successfully restored within {restoreTo}. status code {response.status}.")                          
    except Exception as ex:
        print(f"Error:requestFileRestore error! Exception: {ex}")

# request to remove a file from the server 
def requestFileRemoval(fileName):
    try:
        request = request.getRequest(request.EOp.FILE_DELETE, fileName)
        with request.initializeSocket() as socket:
            request.socketSend(socket, request.pack())
            response = response(socket.recv(Constants.PACKET_SIZE))
            if response.validate(response.EStatus.SUCCESS_BACKUP_REMOVE):
                print(f"File '{fileName}' successfully removed. status code {response.status}.")

    except Exception as ex:
        print(f"Error:requestFileRemoval error! Exception: {ex}")


if __name__ == '__main__':
    try:
        print("Hello im the client and im alive")
        userID = Constants.generateRandomID()
        server, port = parseServerInfo(Constants.SERVER_INFO)
        print(f"Client & Server info:\n\tUserId: {userID}\n\tServer: {server},\tPort: {port}")
        backupList = parseFileList(Constants.BACKUP_INFO)

        #Work work work
        requestFilesList()  # Request file list from server.
        requestFileBackup(backupList[0])  # Backup first file.
        requestFileBackup(backupList[1])  # Backup second file.
        requestFilesList()  # Request file list from server after backing-up two first files.
        requestFileRestore(backupList[0], "tmp")  # Restore first file from server to 'tmp'.
        requestFileRemoval(backupList[0])  # Remove first file from server
        requestFileRestore(backupList[0])  # Restore 1st file from server. Expected error because file is removed.

        print("Client work has done")

    except Exception as ex:
        print(f"Error:Genreal error! Exception: {ex}")

    
