from dataclasses import dataclass
from ...Response import Response, ResponseCode

@dataclass
class RegisterFailureResponse(Response):
    STRUCT_FORMAT = ''
    CODE = ResponseCode.REGISTER_FAILURE