from typing import Type, Dict
from asyncio import (
    IncompleteReadError,
    StreamReader,
    StreamWriter
)

from ..FileManager import FileManager
from ..Response import Response
from ..Database import Database

from .baseRequest import Request
from .requestHeader import RequestHeader
from .requestHeader import RequestCode


class RequestHandler:
    def __init__(self, default_response: Response = None):
        self._request_types: Dict[RequestCode, Type[Request]] = {}
        self._default_response = default_response

    def add_request_type(self, request_type: Type[Request]):
        self._request_types[request_type.CODE] = request_type

    async def handle_request(self, database: Database, file_manager: FileManager, reader: StreamReader, writer: StreamWriter):
        header = await reader.readexactly(RequestHeader.size)
        request_header = RequestHeader.from_bytes(header)
        request_code = request_header.code

        if request_code not in self._request_types:
            response = self._default_response.to_bytes()
            writer.write(response)
            await writer.drain()
            return

        try:
            request_type = self._request_types[request_code]
            await request_type.raw_handler(request_header, database, file_manager, reader, writer)
        except Exception as e:
            response = self._default_response.to_bytes()
            writer.write(response)
            await writer.drain()
            raise e