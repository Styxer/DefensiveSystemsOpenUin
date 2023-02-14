from dataclasses import dataclass
from ...Requet import  RequestCode

import CRCRequest

@dataclass
class CorrectCRCRequest(CRCRequest):
    CODE = RequestCode.CORRECT_CRC