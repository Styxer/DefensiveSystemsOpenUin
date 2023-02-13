from abc import ABC, abstractmethod
from dataclasses import dataclass

from ...constants import SERVER_VERSION
from ...Utils import SerializableClass
from .responseCodes import ResponseCode
from .responseHeader import ResponseHeader 

class Response(ABC, SerializableClass):
    #The response code identifier. Allows the response header to be constructed properly.
    @property
    @staticmethod
    @abstractmethod
    def CODE() -> ResponseCode:
        raise NotImplementedError()

    # Converts the response instance into raw bytes. Appends the response header to the response payload.
    #:return: The constructed respone header appended by the response payload
    def to_bytes(self) -> bytes:      
        payload = super().to_bytes()
        header = ResponseHeader(SERVER_VERSION, self.CODE, self.size)
        return header.to_bytes() + payload