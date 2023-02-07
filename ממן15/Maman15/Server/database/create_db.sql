CREATE TABLE IF NOT EXISTS clients(
  id, BLOB PRIMARY KEY,          --user id 16 bytes(UUID)
  name TEXT NOT NULL,            --user name, 255 bytes
  public_key BLOB,               --RSA public key
  last_seen INTEGER DEFAULT 0,   --seconds since epoch
  aes_key BLOB                   --AES key, 16 bytes
);

CREATE TABLE IF NOT EXISTS files(
    id BLOB PRIMARY KEY,               --file id, 16 bytes(UUID)
    file_name TEXT NOT NULL,           --file name, 255 bytes
    file_path TEXT NOT NULL,           -- Rlative path in the server, 255 bytes
    verified INTEGER DEFAULT FALSE     -- has the checksum been verified by the client(boolean)


);