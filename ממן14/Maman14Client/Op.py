from enum import Enum

 # Request codes
class Op(Enum): 
    FILE_BACKUP = 100  # Save file backup. All fields should be valid.
    FILE_RESTORE = 200  # Restore a file. size, payload unused.
    FILE_DELETE = 201  # Delete a file. size, payload unused.
    FILE_DIR = 202  # List all client's files. name_len, filename, size, payload unused.