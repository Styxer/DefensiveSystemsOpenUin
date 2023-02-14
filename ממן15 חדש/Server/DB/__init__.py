from pathlib import Path
import sys
from time import time
from typing import Optional, NamedTuple
from Client import  Client
from File import  File
import os
import sqlite3

from ...Constants import constants

class Database:
    def __int__(self, filename: str = constants.DB_FILE_NAME):  
        self.file_db = sqlite3.connect(filename)
        self.memorey_db = sqlite3.connect(":memory:")
        self.file_cursor = self.file_db.cursor()
        self.memorey_cursor = self.memorey_db.cursor()     

        with open(constants.SQL_CREATE_FILE, 'r') as sql_create_file:
            create = sql_create_file.read()
        self.execute_script(create)

    #Execute an sql script on db(in memorey and file db)
    #Returns the result of the file db
    def execute_script(self, *args, **kwargs):
       try:
            self.memorey_cursor.executescript(*args,**kwargs)
            return self.file_cursor.executescript(*args, **kwargs)
       except Exception as e:
           print(e)

    #Execute an sql script on db(in memorey and file db)
    #Returns the result of the file db
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

    # region client table methods
    def find_client(self, client_id: bytes = None, name: str = None) -> Optional[Client]:
        if name:
            query = f"SELECT * FROM {constants.CLIENTS_TABLE_NAME} WHERE name =?"
            param = name
        elif client_id:
            query = f"SELECT * FROM {constants.CLIENTS_TABLE_NAME} WHERE id =?"
            param = client_id
        else:
            raise  ValueError('need to specify client id or name to find client') 

        self.execute(query, [param])
        result = self.fetch_one()
        if not result:
            return None
        return Client(*result)

    def is_client_exists(self, *args,**kwargs):
        return  bool(self.find_client(*args, **kwargs))

    def register_client(self, client_id : bytes, name: str):
        if(self.is_client_exists(client_id=client_id, name=name)):
            raise ValueError(f"User already exists client id:{client_id} and nane: {name}") 
        if len(name) > constants.MAX_USERNAME_LENGTH:
            raise ValueError(f"User {name} of length {len(name)} is above the allowed limit {constants.MAX_USERNAME_LENGTH}") 

        query_params = {
            "client_id": client_id,
            "name" : name,
            "last_seen" : int(time())
        }

        self.execute(f"INSERT INTO {constants.CLIENTS_TABLE_NAME} VALUES(:client_id, :name, NULL, :last_seen, NULL", query_params)
        self.commit()

    def set_client_public_key(self, client_id:bytes, public_key: bytes):
        if not self.is_client_exists(client_id=client_id):
            raise ValueError(f"client with id {client_id} exists") 

        query_params = {
            "client_id": client_id,
            "public_key": public_key,
        }

        self.execute(f"UPDATE {constants.CLIENTS_TABLE_NAME} SET public_key=:public_key WHERE id=:client_id", query_params)
        self.commit()

    def set_client_aes_key(self, client_id: bytes, aes_key: bytes):
        if not self.is_client_exists(client_id=client_id):
            raise ValueError(f"client with id {client_id} exists") 

        query_params = {
            "client_id": client_id,
            "aes_key": aes_key,
        }
        self.execute(f"UPDATE {constants.CLIENTS_TABLE_NAME} SET aes_key=:aes_key WHERE id=:client_id", query_params)
        self.commit()
    #endregion

    #region File table methods
    def find_file(self, file_id: bytes = None, file_name : str = None) -> Optional[File]:
        if file_name:
            query = f"SELECT * FROM {constants.FILES_TABLE_NAME} WHERE file_name=?"
            params = file_name
        elif file_id:
            query = f"SELECT * FROM {constants.FILES_TABLE_NAME} WHERE id=?"
            params = file_name
        else:
            raise ValueError('need to specify file id or file name to find file') 

        self.execute(query, [params])
        result = self.fetch_one()
        if not result:
            return None
        return File(*result)

    def is_file_exists(self, *args,**kwargs):
        return  bool(self.find_file(*args, **kwargs))

    def create_file(self, file_id: bytes, file_name: str, file_path:str):
        query_params = {
            "file_id": file_id,
            "file_name": file_name,
            "file_path" : file_path
        }
        self.execute(f"INSERT INTO {constants.FILES_TABLE_NAME} VALUES (:file_id, :file_name, _file_path, NULL)", query_params)
        self.commit()

    def set_file_verification(self, file_id: bytes, verification: bool):
        if not self.is_file_exists(file_id=file_id):
            raise  ValueError(f"File with id {file_id} does not exists") 

        query_params = {
            "file_id" : file_id,
            "verification" : int(verification)
        }
        self.execute(f"UPDATE {constants.FILES_TABLE_NAME} SET verified=:verification WHERE id=:file_id", query_params)
        self.commit()

    def delete_file(self, file_id: bytes):
        if not self.is_file_exists(file_id=file_id):
            raise  ValueError(f"File with id {file_id} does not exists") 
        self.execute(f"DELETE FROM {constants.FILES_TABLE_NAME} WHERE file_id=?", [file_id])
        self.commit()


    #endregion
'''   
if __name__ == '__main__':
    database = Database.__init__(Database)     
    database = Database()
    database.register_client(111, "DDD")
    database.register_client(Database,222, "aaa")
    database.register_client(Database,333, "bbb")
    database.register_client(Database,111, "bbb")
'''
