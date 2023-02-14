from dataclasses import dataclass
from ...Requet import  RequestCode

import CRCRequest

@dataclass
class IncorrectCRCFinalRequest(CRCRequest):
    CODE = RequestCode.INCORRECT_CRC_FINAL