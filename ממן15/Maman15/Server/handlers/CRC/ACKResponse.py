from dataclasses import dataclass
from ...Response import Response, ResponseCode

@dataclass
class ACKResponse(Response):
    STRUCT_FORMAT = ''
    CODE = ResponseCode.ACK
