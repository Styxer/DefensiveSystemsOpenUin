from typing import NamedTuple
from pathlib import Path
from uuid import uuid4

from .Server.database import Database, File, Client

class FileManager:
    def __init__(self, database: Database) -> None:
        self.database = database
        
    def create_file(self, client: Client, filename : str) -> File:
        file_id = uuid4().bytes
        file_extension = Path(filename).suffix
        
        directory = Path(f'./user_files/{client.client_id.hex()}')
        directory.mkdir(parents=True, exist_ok=True)

        path = directory.joinpath(f'{file_id.hex()}{file_extension}')
        self._database.create_file(file_id, filename, str(path))
        return self._database.find_file(file_name=filename)
    
    def append_to_file(self, file: File, content: bytes):
        with open(file.path, 'ab') as output_file:
            output_file.write(content)
    
    def delete_file(self, file: File):
        Path(file.path).unlink(missing_ok=True)