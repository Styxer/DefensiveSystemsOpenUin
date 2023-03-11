Server

The code is separated Into this main components:

1.Main - The main logic of the server. Uses asyncio to control the TCP connection, listening on a port specified in  port.info. Each incoming request is sent to the RequestHandler instance, which is dependency-injected with an instance of Database and FileManager.
2.File Manager - A simple class to manage the uploaded files, in relation to the database and the filesystem. In charge of file and in memorey CRUD (Create, Update, Delete) operations in front of the database and the filesystem.
3.Config  - Context manager to read the port config file.
4.Request - Package in charge of parsing and handling requests from clients, exporting two main functional interfaces:
   4a.RequestHandler - A general manager of requests, talking to the asyncio level and extracting bytes from the socket. All request classes register themselves in this handler, and it parses the request header and calls the appropriate request class.
   4b.Request - Abstract base request class, inheriting from SerializableClass and exporting a class property code indicating the requst code it's made to handle and instance function handle(header) -> Response, in charge of handling an already parsed request and returning the appropriate response.
5.Response -In charge of constructing server responses. Exports one main functional interface - Resposne - which is an abstract base class inheriting from SerializableClass, overriding the to bytes function to create the header in-place. It also exposes an abstract class property code to indicate the resposne code associated with it.
6.Handlers - Package in charge of handling requests. Implements the Request and Response interface. One specific handler to note is the FileUploadRequest handler, which overrides the class method raw_handler. This is in order for it to support both encryption and variable length requests - a feature that's not required on other requests since they all have constant, small lengths (and file transfers can be theoretically 4GB in size). Therefore the handler overrides the raw_handler method which reads the request from the socket in chunks sized AES_BLOCK_SIZE.
7.Database - Package in charge of database operations, against two SQLite databases - one stored in the server.db file and one stored in-memory.


Client

The code is separated Into this main components:

1.Main - The main logic of the client. uses the standart tcp to control  the TCP connection. binding on a port specified in port.info.
2.User - In charge of what the user can do
3.Reosponse - A package in charge of handling the response from the server, uses AES and sets the payload accordingly
4.Request - A package in charge of handling the request that is send the server, uses CRC to check if there are no errors in sending the data to the server
5.Encryption - A package in charege of handling of encrypting the data before it sent to the server, uses AES and RSA as its base algoritams
6.Config - A package that in charge of two smaller parts:
	6a.Client Config - A simple class that handles of all user config(client id, public and private key and its user name)
	6b.Transfer Config - A simple class that handles the info transfered to the server(server address, port, files to send) 
7.Utils - A small set of utilities that do:
	7a. Checksum algoritam(using Boost/CRC)
	7b. Serialize 
	7c. Constatns that are used across the client