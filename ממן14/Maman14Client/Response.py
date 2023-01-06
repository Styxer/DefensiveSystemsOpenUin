from Payload import Payload


class Response:
    def __init__(self, data):
        self.version = 0
        self.status = 0
        self.nameLen = 0
        self.filename = None  # filename
        self.payload = Payload()