from Constants import Constants
from Payload import Payload

import struct


class Request:
    def __init__(self, userId):
        self.userId = userId
        self.version = Constants.CLIENT_VERSION
        self.op = 0  # Request Code
        self.fileNameLen = 0
        self.fileName = b""
        self.payload = Payload()

    def sizeWithoutPayload(self):
        return 12 + self.fileNameLen  # userId(4), version(1), op(1) , nameLen(2), payload size(4)

    # Little Endian(<) pack the Request
    def pack(self):
        try:
            leftover = Constants.PACKET_SIZE - self.sizeWithoutPayload()
            if self.payload.size < leftover:
                leftover = self.payload.size
            return struct.pack(f"<IBBH{self.fileNameLen}sL{leftover}s",
                               self.userId, self.version, self.op,
                               self.fileNameLen, self.fileName,
                               self.payload.size, self.payload.payload[:leftover])
        except Exception as ex:
            return 0

    # Initialize a request with Request Code and filename
    @staticmethod
    def getRequest(op, userId, fileName="", ):
        request = Request(userId)
        request.op = op.value
        request.fileName = bytes(fileName, 'utf-8')
        request.fileNameLen = len(request.fileName)  # shouldn't exceed max filename length.
        if request.fileNameLen > Constants.MAX_NAME_LEN:
            Constants.stopClient(f"Filename exceeding length {Constants.MAX_NAME_LEN}! Filename: {fileName}")
        return request
