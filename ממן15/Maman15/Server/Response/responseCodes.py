from enum import IntEnum, unique

@unique
class ResponseCode(IntEnum):
    REGISTER_SUCCESS = 2100
    REGISTER_FAILURE = 2101
    AES_KEY_EXCHANGE = 2102
    FILE_UPLOAD_SUCCESS = 2103
    ACK = 2104
    SERVER_ERROR = 2105