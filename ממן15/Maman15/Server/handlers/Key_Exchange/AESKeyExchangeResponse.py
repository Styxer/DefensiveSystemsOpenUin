from dataclasses import dataclass

from Crypto.Random import get_random_bytes
from Crypto.Cipher import PKCS1_OAEP
from Crypto.PublicKey import RSA

from . import Request, RequestCode, RequestHeader
from ...response import Response, ResponseCode
from ....constants import (
    CLIENT_ID_LENGTH,
    MAX_USERNAME_LENGTH,
    X509_PUBLIC_KEY_LENGTH,
    AES_KEY_LENGTH,
    RSA_BLOCK_SIZE
)

@dataclass
class AESKeyExchangeResponse(Response):
    STRUCT_FORMAT = f'<{CLIENT_ID_LENGTH}s{RSA_BLOCK_SIZE}s'
    CODE = ResponseCode.AES_KEY_EXCHANGE
    client_id: bytes
    encrypted_aes_key: bytes