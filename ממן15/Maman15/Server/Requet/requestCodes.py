from enum import IntEnum, unique

@unique
class RequestCode(IntEnum):
    USER_REGISTERATION = 1100
    PUBLIC_KEY_EXCHANGE = 1101
    FILE_UPLOAD = 1103
    CORRECT_CRC = 1104
    INCORRECT_CRC_RETRY = 1105
    INCORRECT_CRC_FINAL = 1106