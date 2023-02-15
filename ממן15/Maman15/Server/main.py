from asyncio import  IncompleteReadError, StreamReader, StreamWriter, start_server, run
from .Response import ResponseHeader, ResponseCode
from .FileManager import FileManager
from .Requet import RequestHandler
from .Database import Database
from .Handlers import HANDLERS
from .config import config_file
from .Constants import SERVER_LITSEN_IP

DEFAULT_RESPONSE = ResponseHeader(server_version = 0, code = ResponseCode.SERVER_ERROR, payload_size = 0)

REQUEST_HANDLER = RequestHandler(default_response = DEFAULT_RESPONSE)

DATABASE = Database()

FILE_MANAGER = FileManager(DATABASE)

async def handle_client(reader: StreamReader, writer: StreamWriter):
    address, port = writer.get_extra_info('peername')
    print(f'[{address}:{port}] Connected!')
    while True:
        try:
            await REQUEST_HANDLER.handle_request(DATABASE, FILE_MANAGER, reader, writer)
        except IncompleteReadError:
            break
        except ConnectionAbortedError as e:
            print(f'[{address}:{port}] Got aborted! {e}')
            break
        except ConnectionResetError as e:
            print(f'[{address}:{port}] Got reset! {e}')
            break
        except Exception as e:
            print(f'[{address}:{port}] Got got an exception {e}!')
            break

    if not writer.is_closing():
        writer.close()
        await writer.wait_closed()

    print(f'server  [{address}:{port}] ended')

async def listen(port: int):
    server = await start_server(handle_client, SERVER_LITSEN_IP , port)
    for socket in server.sockets:
        interface, port = socket.getsockname()
        print(f'Listening on {interface}:{port}')

    async with server:
        await server.serve_forever()


def main():
    for request_type in HANDLERS:
        REQUEST_HANDLER.add_request_type(request_type)

    try:
        with config_file() as port:
            run(listen(port))
    except KeyboardInterrupt:
        print('Goodbye!')
    except Exception as e:
        print(f'error happened {e}!')

    DATABASE.close()


if __name__ == '__main__':
    main()