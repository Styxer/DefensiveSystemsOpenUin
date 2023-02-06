from pathlib import Path
from time import time
from typing import Optional, NamedTuple
from Client import  Client
from File import  File
import sqlite3

from ..constants import constants # TODO


FILE_NAME = Path(__file__).parent.joinpath(SQL_CREATE_FILE).resolve()

class Database:
    def __int__(self, file_name : str = SQL_CREATE_FILE):
        self.file_db = sqlite3.connect(file_name)
        self.memorey_db = sqlite3.connect(":memory:")
        self.file_cursor = self.file_db.cursor()
        self.memorey_cursor = self.memorey_db.cursor()

        with open(SQL_CREATE_FILE, 'r') as sql_create_file:
            create = sql_create_file.read()
        self.execute_script(create)

    #Execute an sql script on db(in memorey and file db)
    #Returns the result of the file db
    def execute_script(self, *args, **kwargs):
        self.memorey_cursor.execute_script(*args,**kwargs)
        return self.file_cursor.execute_script(*args, **kwargs)

    #?
    def execute(self, *args, **kwargs):
        self.memorey_cursor.execute(*args, **kwargs)
        return self.file_cursor.execute(*args, **kwargs)

    #fetch all results
    def fetch_all(self):
        self.memorey_cursor.fetchall()
        return self.file_cursor.fetchall()

    #fetch 1st row
    def fetch_one(self):
        self.memorey_cursor.fetchone()
        return self.file_cursor.fetchone()

    #commit action to the db
    def commit(self):
        self.memorey_db.commit()
        self.file_db.commit()

    #close db connection
    def close(self):
        self.memorey_db.close()
        self.file_db.close()

    def find_client(self, client_id: Bytes = None, name: str = None) -> Optional[Client]
        if name:
            query = f"SELECT * FROM {constants.CLIENTS_TABLE_NAME} WHERE name =?"
            param = name
        elif: client_id:
            query = f"SELECT * FROM {constants.CLIENTS_TABLE_NAME} WHERE id =?"
            param = client_id
        else:
            raise  ValueError('need to specify client id or name to find client') from error
        self.execute(query, [param])
        result = self.fetch_one()
        if not result:
            return None
        result Client(*result)

