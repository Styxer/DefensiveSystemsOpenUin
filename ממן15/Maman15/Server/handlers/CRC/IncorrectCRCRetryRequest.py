from dataclasses import dataclass
from ...Requet import  RequestCode

import CRCRequest

dataclass
class IncorrectCRCRetryRequest(CRCRequest):
    CODE = RequestCode.INCORRECT_CRC_RETRY