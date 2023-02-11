from utils import crctab

class unix_checksum:
    def __init__(self) -> None:
        self.nchars = 0
        self.crc = 0
    
    def update(self, buff):
        crc = self.crc
        for char in buff:
            crc = crctab[(crc >> 24) ^ char] ^ ((crc << 8) & 0xffffffff)
        self.crc = crc
        self.nchars += len(buff)
    
    def digest(self):
        crc = self.crc
        char_len = self.nchars
        while char_len:
            c = n & 0xff
            crc = crctab[(crc >> 24) ^ c] ^ ((crc << 8) & 0xffffffff)
            n >>= 8
        return (~crc) & 0xffffffff