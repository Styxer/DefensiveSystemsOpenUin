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
            self.version, self.status, self.nameLen = struct.unpack("<BHH", data[:5])
            offset = 5
            self.fileName = struct.unpack(f"<{self.nameLen}s", data[offset:offset + self.nameLen])
            self.fileName = self.fileName[0].decode('utf-8')
            offset += self.nameLen
            self.payload.size = struct.unpack("<I", data[offset:offset + 4])
            self.payload.size = self.payload.size[0]
            offset += 4
            leftover = Constants.PACKET_SIZE - offset
            if self.payload.size < leftover:
                leftover = self.payload.size
            self.payload.payload = struct.unpack(f"<{leftover}s", data[offset:offset + leftover])
            self.payload.payload = self.payload.payload[0]
        except Exception as e:
            print(e)

    #Validates response status
    def validate(self, expected_status):
        """ Validate response status """
        isValid = False
        if self.status is None:
            print("Invalid response received!")
        elif self.status == Status.ERROR_GENERIC.value:
            print(f"Generic Error received! status code {self.status}.")
        elif self.status == Status.ERROR_NO_FILES.value:
            print(f"Client has no files! status code {self.status}.")
        elif self.status == Status.ERROR_NOT_EXIST.value:
            tmp_str = "" if (self.filename is None or self.filename == "") else f"'{self.filename}'"
            print(f"Requested File {tmp_str} doesn't exists! status code {self.status}.")
        elif expected_status.value != self.status:
            print(f"Unexpected server response {self.status}!")
        else:
            isValid = True
        return isValid