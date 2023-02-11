from dataclasses import dataclass

from Crypto.Random import get_random_bytes
from Crypto.Cipher import PKCS1_OAEP
from Crypto.PublicKey import RSA

import AESKeyExchangeResponse

from ..request import Request, RequestCode, RequestHeader
from ..response import Response, ResponseCode
from ..constants import (
    CLIENT_ID_LENGTH,
    MAX_USERNAME_LENGTH,
    X509_PUBLIC_KEY_LENGTH,
    AES_KEY_LENGTH,
    RSA_BLOCK_SIZE
)

@dataclass
class PublicKeyExchangeRequest(Request):
    STRUCT_FORMAT = f'<{MAX_USERNAME_LENGTH}s{X509_PUBLIC_KEY_LENGTH}s'
    CODE = RequestCode.PUBLIC_KEY_EXCHANGE
    user_name: str
    public_key: bytes

    def handle(self, header: RequestHeader) -> Response:
        client_id = header.client_id
        aes_key = get_random_bytes(AES_KEY_LENGTH)
        self.database.set_client_public_key(client_id, self.public_key)
        self.database.set_client_aes_key(client_id, aes_key)

        public_key = RSA.import_key(self.public_key)
        cipher = PKCS1_OAEP.new(public_key)
        encrypted_aes_key = cipher.encrypt(aes_key)
        return AESKeyExchangeResponse(client_id, encrypted_aes_key)

