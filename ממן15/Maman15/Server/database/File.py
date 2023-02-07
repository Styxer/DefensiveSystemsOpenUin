from typing import  NamedTuple
from dataclasses import dataclass

@dataclass
class File(NamedTuple):
    file_id : bytes
    name : str
    path : str
    verified: bool