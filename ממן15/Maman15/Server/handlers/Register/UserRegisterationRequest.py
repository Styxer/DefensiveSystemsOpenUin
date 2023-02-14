from dataclasses import dataclass
from uuid import uuid4

import RegisterSuccessResponse
import RegisterFailureResponse

from ...Requet import Request, RequestCode, RequestHeader
from ...Response import Response

from ...Constants import MAX_USERNAME_LENGTH

@dataclass
class UserRegisterationRequest(Request):
    STRUCT_FORMAT = f'<{MAX_USERNAME_LENGTH}s'
    CODE = RequestCode.USER_REGISTERATION
    user_name: bytes

    def handle(self, header: RequestHeader) -> Response:
        try:
            user_id = uuid4().bytes
            name = self.user_name.decode().strip('\x00')
            self.database.register_client(user_id, name)
            return RegisterSuccessResponse(user_id)
        except ValueError:
            return RegisterFailureResponse()