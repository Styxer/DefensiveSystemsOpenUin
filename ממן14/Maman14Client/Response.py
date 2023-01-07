import struct
from Payload import Payload
from Constants import Constants
from Status import Status

class Response:
    def __init__(self, data):
        self.version = 0
        self.status = 0
        self.FileNameLen = 0
        self.fileName = None 
        self.payload = Payload()
        try:
            self.version, self.status, self.FileNameLen = struct.unpack("<BHH", data[:5])
            offset = 5
            self.fileName = struct.unpack(f"<{self.FileNameLen}s", data[offset:offset + self.FileNameLen])
            self.fileName = self.fileName[0].decode('utf-8')
            offset += self.FileNameLen
            self.payload.size = struct.unpack("<I", data[offset:offset + 4])
            self.payload.size = self.payload.size[0]
            offset += 4
            leftover = Constants.PACKET_SIZE - offset
            if self.payload.size < leftover:
                leftover = self.payload.size
            self.payload.payload = struct.unpack(f"<{leftover}s", data[offset:offset + leftover])
            self.payload.payload = self.payload.payload[0]
        except Exception as ex:
            print(ex)

    #Validates response status
    def validate(self, expected_status):
        isValid = False
        if self.status is None:
            print("Error: Invalid response received!")
        elif self.status == Status.ERROR_GENERIC.value:
            print(f"Error:Generic Error received! status code {self.status}.")
        elif self.status == Status.ERROR_NO_FILES.value:
            print(f"Error:Client has no files! status code {self.status}.")
        elif self.status == Status.ERROR_NOT_EXIST.value:
            errStr = "" if (self.fileName is None or self.fileName == "") else f"'{self.fileName}'"
            print(f"Error:Requested File {errStr} doesn't exists! status code {self.status}.")
        elif expected_status.value != self.status:
            print(f"Error:Unexpected server response {self.status}!")
        else:
            isValid = True
        return isValid