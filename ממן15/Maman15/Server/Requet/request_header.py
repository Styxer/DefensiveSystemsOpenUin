from dataclasses import dataclass

from ...constants import CLIENT_ID_LENGTH
from ...Utils import SerializableClass

from .codes import RequestCode

#Defines the shared header sent in the beginning of all requests to the server.
@dataclass
class RequestHeader(SerializableClass):
    STRUCT_FORMAT = f'<{CLIENT_ID_LENGTH}sBHI'
    client_id: bytes
    client_version: int
    code: RequestCode
    payload_size: int