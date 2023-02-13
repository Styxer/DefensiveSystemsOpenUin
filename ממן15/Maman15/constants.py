# Length of the client ID in bytes
CLIENT_ID_LENGTH = 16

# Max username length, in bytes (including a null terminator)
MAX_USERNAME_LENGTH = 255

# Max username length, in bytes (including a null terminator)
MAX_FILENAME_LENGTH = 255

#Server name
DB_FILE_NAME = "server.db"

#SQL create file name
SQL_CREATE_FILE = "create_db.sql"

#clients table name in DB
CLIENTS_TABLE_NAME = "clients"

#files table name in DB
FILES_TABLE_NAME = "files"

# X509 RSA public key length, including the header
X509_PUBLIC_KEY_LENGTH = 160

# AES key length, in bytes
AES_KEY_LENGTH = 16

# RSA block size, in bytes
RSA_BLOCK_SIZE = 128

# AES block size, in bytes
AES_BLOCK_SIZE = 16

# AES IV. As defined in the protocol, all zeroes.
AES_IV = b'\x00' * AES_BLOCK_SIZE

# Chunk size for CRCing large files, in bytes
CRC_CHUNK_SIZE = 128

# Server version, as defined in the assignment.
SERVER_VERSION = 3