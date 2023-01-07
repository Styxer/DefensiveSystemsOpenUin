import socket
from Maman14Client import stopClient
from Constants import PACKET_SIZE

class SocketHandler:
    #Initialize a TCP/IP Socket with parsed server parameters.    
    def initializeSocket(server, port):
        try:
            s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            s.connect((server, port))
        except Exception as e:
            stopClient(f"initializeSocket Exception: {e}!")
    
    # sending socket with the right PACKET_SIZE
    def sendSocket(socket, buffer):
         bytes_size = len(buffer)
         if bytes_size < PACKET_SIZE:
            buffer += bytearray(PACKET_SIZE - bytes_size)
         elif bytes_size > PACKET_SIZE:
            buffer = buffer[:PACKET_SIZE]
         socket.send(buffer)
