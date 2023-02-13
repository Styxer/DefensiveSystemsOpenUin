from dataclasses import dataclass

from Crypto.Random import get_random_bytes
from Crypto.Cipher import PKCS1_OAEP
from Crypto.PublicKey import RSA

from ...Requet import Request, RequestCode, RequestHeader
from ...Response import Response, ResponseCode
from ... import (
    CLIENT_ID_LENGTH,
    MAX_FILENAME_LENGTH
)

import CRCRequest

@dataclass
class IncorrectCRCFinalRequest(CRCRequest):
    CODE = RequestCode.INCORRECT_CRC_FINAL