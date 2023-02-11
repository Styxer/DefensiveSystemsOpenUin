from dataclasses import dataclass
from asyncio import (
    StreamReader,
    StreamWriter
)

from Crypto.Cipher import AES
from Crypto.Util.Padding import unpad

from ...Requet import Request, RequestCode, RequestHeader
from ...Response import Response, ResponseCode
from ...file_manager import FileManager
from ....Utils import unix_checksum
from ...database import Database
from ...constants import (
    CLIENT_ID_LENGTH,
    MAX_FILENAME_LENGTH,
    AES_BLOCK_SIZE,
    AES_IV
)

@dataclass
class FileUploadSuccessResposne(Response):
    STRUCT_FORMAT = f'<{CLIENT_ID_LENGTH}sI{MAX_FILENAME_LENGTH}sI'
    CODE = ResponseCode.FILE_UPLOAD_SUCCESS
    client_id: bytes
    content_size: int
    filename: str
    checksum: int