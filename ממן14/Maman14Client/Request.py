from Constants import Constants;
from Payload import Payload;
from Maman14Client import client
import struct


class Request:
    def __init__(self):
        self.userId = Constants.getUserID  # User ID
        self.version = Constants.CLIENT_VERSIONCLIENT_VER  # Client Version
        self.op = 0  # Request Code
        self.nameLen = 0  # filename length
        self.filename = b""  # filename
        self.payload = Payload()

    def sizeWithoutPayload(self):
        return self.userId + self.version + self.op + self.payload + self.nameLen

    def pack(self):
        leftover = Constants.PACKET_SIZE - self.sizeWithoutPayload()
        if self.payload.size < leftover:
            leftover = self.payload.size
            return struct.pack(f"<IBBH{self.nameLen}sL{leftover}s",
                           self.userId, self.version, self.op,
                           self.nameLen, self.filename,
                           self.payload.size, self.payload.payload[:leftover])

    @staticmethod
    def getRequest(op, filename=""):
        request = Request()
        request.op = op.value
        request.filename = bytes(filename, 'utf-8')
        request.nameLen = len(request.filename)  # shouldn't exceed max filename length.
        if request.nameLen > Constants.MAX_NAME_LEN:
            client.stopClient(f"Filename exceeding length {Constants.MAX_NAME_LEN}! Filename: {filename}")
        return request
        