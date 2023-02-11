from dataclasses import dataclass
from uuid import uuid4

from ..request import Request, RequestCode, RequestHeader
from ..response import Response, ResponseCode
from ..database import Database
from ..constants import (
    CLIENT_ID_LENGTH,
    MAX_USERNAME_LENGTH
)

@dataclass
class RegisterSuccessResponse(Response):
    STRUCT_FORMAT = f'<{CLIENT_ID_LENGTH}s'
    CODE = ResponseCode.REGISTER_SUCCESS
    client_id: bytes