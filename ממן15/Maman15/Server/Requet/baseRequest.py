from asyncio import StreamReader, StreamWriter
from abc import ABC, abstractmethod

from ..FileManager import FileManager
from ...Utils import SerializableClass
from ..Response import Response
from ..Database import Database

from .requestHeader import RequestHeader
from .requestCodes import RequestCode


class Request(ABC, SerializableClass):
    database: Database
    file_manager: FileManager

    @property
    @staticmethod
    @abstractmethod
    #The request code identifier. Allows the server class to call the appropriate
    #request handler based on the request code in the header.
    def CODE() -> RequestCode:        
        raise NotImplementedError()

    #Handles requests as they're received by the server. This method is called by
    #the Server::handle_request method, and can be overridden by subclasses. This method
    #isn't in charge of closing the request - only parsing the request, acting on it and
    #writing the response back to the client.
    #param header: The parsed request header. Passed down to the abstract handle method.
    #param reader: The StreamReader used by the client.
    #param writer: The StreamWriter used by the client.
    @classmethod
    async def raw_handler(cls, header: RequestHeader, database: Database, file_manager: FileManager,
                          reader: StreamReader, writer: StreamWriter):
       
        print(f'Received a {cls.CODE.name} request')
        data = await reader.readexactly(cls.size)
        print(f'Received {len(data)} bytes: {data.hex()}')
        request = cls.from_bytes(data)
        request.database = database
        request.file_manager = file_manager
        response = request.handle(header)
        print(f'Sending {response}')
        writer.write(response.to_bytes())
        await writer.drain()

    #Handles the parsed request and returns a response instance according to it.
    #param header: The parsed request header.
    #return: A Response instance, according to the protocol.
    @abstractmethod
    def handle(self, header: RequestHeader) -> Response:        
        raise NotImplementedError()