from typing import Optional, NamedTuple
from dataclasses import dataclass

@dataclass
class Client(NamedTuple):
    client_id : bytes
    name : str
    public_kye : Optional[bytes]
    last_seen : int
    aes_key : Optional[bytes]