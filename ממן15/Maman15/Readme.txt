Server

The server code is divided into several main components, including the Main component, which is responsible for the server's main logic and uses asyncio to control the TCP connection. This component listens on a specified port and sends incoming requests to the RequestHandler instance. The RequestHandler is dependency-injected with instances of Database and FileManager.

The FileManager component is a simple class that manages uploaded files in relation to the database and filesystem. It handles CRUD operations (Create, Update, Delete) for files both in-memory and on the filesystem.

The Config component is a context manager that reads the port config file, and the Request component is responsible for parsing and handling client requests. It exports two main functional interfaces: RequestHandler, which is a general manager of requests, and Request, which is an abstract base request class that handles parsed requests and returns appropriate responses. The Request component also includes an abstract class property called "code" that indicates the request code associated with it.

The Response component is responsible for constructing server responses and exports one main functional interface - Response - which is an abstract base class inheriting from SerializableClass. It overrides the to bytes function to create the header in-place and includes an abstract class property called "code" to indicate the response code associated with it.

The Handlers component is in charge of handling requests and implements the Request and Response interface. The FileUploadRequest handler is a specific handler that overrides the raw_handler method to support encryption and variable length requests. This feature is not required for other requests since they have constant, small lengths, and file transfers can be up to 4GB in size. The Database component is responsible for database operations against two SQLite databases - one stored in the server.db file and one stored in-memory.


Client

The client code is divided into several main components. The Main component is responsible for the client's main logic and uses standard TCP to control the connection. It binds to a port specified in port.info.

The User component is in charge of determining what actions the user can perform. The Response component is responsible for handling responses from the server and uses AES to set the payload accordingly. The Request component handles sending requests to the server and uses CRC to check for errors in the data transmission.

The Encryption component is responsible for encrypting the data before it is sent to the server and uses AES and RSA as its base algorithms.

The Config component is responsible for two smaller parts. The Client Config class handles all user configurations, such as client ID, public and private keys, and user name. The Transfer Config class handles the information transferred to the server, such as server address, port, and files to send.

The Utils component includes a small set of utilities that perform various tasks. The Checksum algorithm uses Boost/CRC to ensure data integrity. Serialize is responsible for serialization, and Constants contains constants used across the client.