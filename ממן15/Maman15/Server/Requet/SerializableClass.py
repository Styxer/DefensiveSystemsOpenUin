from struct import pack, unpack, calcsize
from abc import ABC, abstractmethod

#Defines a serializable class that uses the class properties in order to convert to/from bytes.
class SerializableClass:
    
    @property
    @abstractmethod
    # A struct format that will be used to convert to/from bytes. The default implementation throws a NotImplementedError.
    def STRUCT_FORMAT(self) -> str:
        raise NotImplementedError()
    
    @classmethod
    @property
    #Calculates the size of the class struct format.
    def size(cls) -> int:
        return calcsize(cls.STRUCT_FORMAT)
    
    """
        Creates a new instance of the class from raw bytes.
        param data: The raw bytes that match the class struct format
        return: An instance of the class created using these bytes
    """
    @classmethod
    def from_bytes(cls, data: bytes):
        unpacked_data = unpack(cls.STRUCT_FORMAT, data)
        return cls(*unpacked_data)
    
    """
        Converts the created instance into raw bytes.
        :return: The raw bytes created using the class struct format
    """
    def to_bytes(self) -> bytes:
        values = (value for value in self.__dict__.values())
        return pack(self.STRUCT_FORMAT, *values)