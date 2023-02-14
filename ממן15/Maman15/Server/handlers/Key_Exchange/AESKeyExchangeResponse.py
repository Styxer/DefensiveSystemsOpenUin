from dataclasses import dataclass

from ...Response import Response, ResponseCode
from ...Constants import CLIENT_ID_LENGTH, RSA_BLOCK_SIZE    

@dataclass
class AESKeyExchangeResponse(Response):
    STRUCT_FORMAT = f'<{CLIENT_ID_LENGTH}s{RSA_BLOCK_SIZE}s'
    CODE = ResponseCode.AES_KEY_EXCHANGE
    client_id: bytes
    encrypted_aes_key: bytes