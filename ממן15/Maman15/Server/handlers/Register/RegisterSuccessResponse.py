from dataclasses import dataclass

from ...Response import Response, ResponseCode
from ...Constants import CLIENT_ID_LENGTH

@dataclass
class RegisterSuccessResponse(Response):
    STRUCT_FORMAT = f'<{CLIENT_ID_LENGTH}s'
    CODE = ResponseCode.REGISTER_SUCCESS
    client_id: bytes