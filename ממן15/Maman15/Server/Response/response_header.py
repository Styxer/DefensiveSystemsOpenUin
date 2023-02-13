from dataclasses import dataclass

from ...constants import SERVER_VERSION
from ...Utils import SerializableClass
from .responseCodes import ResponseCode

@dataclass
class ResponseHeader(SerializableClass):
    STRUCT_FORMAT = '<BHI'
    server_version: int
    code: ResponseCode
    payload_size: int