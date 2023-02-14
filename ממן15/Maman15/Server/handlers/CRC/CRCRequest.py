from dataclasses import dataclass
from ...Requet import Request, RequestCode, RequestHeader
from ...Response import Response
from ... import CLIENT_ID_LENGTH,  MAX_FILENAME_LENGTH

import ACKResponse

@dataclass
class CRCRequest(Request):
    STRUCT_FORMAT = f'<{CLIENT_ID_LENGTH}s{MAX_FILENAME_LENGTH}s'
    client_id: bytes
    filename: bytes

    def handle(self, header: RequestHeader) -> Response:
        filename = self.filename.decode().strip('\x00')
        file = self.database.find_file(file_name=filename)

        verified = self.CODE is RequestCode.CORRECT_CRC
        if not verified:
            self.file_manager.delete_file(file)

        self.database.set_file_verification(file.file_id, verified)
        return ACKResponse()
