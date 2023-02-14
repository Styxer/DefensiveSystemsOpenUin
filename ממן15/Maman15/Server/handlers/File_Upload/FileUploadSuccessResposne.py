from dataclasses import dataclass
from ...Response import Response, ResponseCode
from ...Constants import   CLIENT_ID_LENGTH, MAX_FILENAME_LENGTH

@dataclass
class FileUploadSuccessResposne(Response):
    STRUCT_FORMAT = f'<{CLIENT_ID_LENGTH}sI{MAX_FILENAME_LENGTH}sI'
    CODE = ResponseCode.FILE_UPLOAD_SUCCESS
    client_id: bytes
    content_size: int
    filename: str
    checksum: int