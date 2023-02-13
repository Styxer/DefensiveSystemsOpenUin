from dataclasses import dataclass
from uuid import uuid4

from ...Requet import Request, RequestCode, RequestHeader
from ...Response import Response, ResponseCode
from ...Database import Database
from ....constants import (
    CLIENT_ID_LENGTH,
    MAX_USERNAME_LENGTH
)

@dataclass
class RegisterFailureResponse(Response):
    STRUCT_FORMAT = ''
    CODE = ResponseCode.REGISTER_FAILURE