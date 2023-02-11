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
from ...Utils import unix_checksum
from ...database import Database
from ...constants import (
    CLIENT_ID_LENGTH,
    MAX_FILENAME_LENGTH,
    AES_BLOCK_SIZE,
    AES_IV
)

import FileUploadSuccessResposne

@dataclass
class FileUploadRequest(Request):
    STRUCT_FORMAT = f'<{CLIENT_ID_LENGTH}sI{MAX_FILENAME_LENGTH}s'
    CODE = RequestCode.FILE_UPLOAD
    client_id: bytes
    content_size: int
    filename: str

    # Overridden to read and process in chunks.
    @classmethod
    async def raw_handler(cls, header: RequestHeader, database: Database, file_manager: FileManager,
                          reader: StreamReader, writer: StreamWriter):        
        inner_header_data = await reader.readexactly(cls.size)
        inner_header = cls.from_bytes(inner_header_data)

        client = database.find_client(client_id=header.client_id)
        filename = inner_header.filename.decode().strip('\x00')
        print(f'Got upload request for {filename}\t Inner header {inner_header}')       
        file = file_manager.create_file(client, filename)
        cipher = AES.new(client.aes_key, AES.MODE_CBC, iv=AES_IV)
        checksum = unix_checksum()

        blocks = inner_header.content_size // AES.block_size
        for _ in range(blocks):
            encrypted_block = await reader.readexactly(AES.block_size)
            block = cipher.decrypt(encrypted_block)
            file_manager.append_to_file(file, block)
            checksum.update(block)

        print(f'file was written  to {file.path}')

        response = FileUploadSuccessResposne(client.client_id, inner_header.content_size,
                                             file.name.encode(), checksum.digest())
        response_bytes = response.to_bytes()
        writer.write(response_bytes)
        await writer.drain()

    def handle(self, header: RequestHeader) -> Response:
        pass

