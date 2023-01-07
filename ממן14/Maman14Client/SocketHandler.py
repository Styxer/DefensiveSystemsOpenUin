import socket as Socket
from Constants import Constants



class SocketHandler:
    #Initialize a TCP/IP Socket with parsed server parameters.   
    
    def initializeSocket(server, port):
        try:
            global socket
            socket = Socket.socket(Socket.AF_INET, Socket.SOCK_STREAM)
            socket.connect((server, port))
           
        except Exception as ex:
            Constants.stopClient(f"initializeSocket Exception: {ex}!")
    
    # sending socket with the right PACKET_SIZE
    def sendSocket(buffer):
        try:
            global socket
            bytes_size = len(buffer)
            if bytes_size < Constants.PACKET_SIZE:
                buffer += bytearray(Constants.PACKET_SIZE - bytes_size)
            elif bytes_size > Constants.PACKET_SIZE:
                buffer = buffer[:Constants.PACKET_SIZE]
            socket.send(buffer)
        except Exception as ex:
            Constants.stopClient(f"sendSocket Exception: {ex}!") 


    def reciveData(size):
         try:
            global socket
            return socket.recv(size)
         except Exception as ex:
            Constants.stopClient(f"reciveData Exception: {ex}!") 
  
    def closeSocket():
        global socket
        socket.close()