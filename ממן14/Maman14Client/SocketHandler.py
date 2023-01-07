import socket

from Constants import Constants

class SocketHandler:
    #Initialize a TCP/IP Socket with parsed server parameters.    
    def initializeSocket(server, port):
        try:
            s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            s.connect((server, port))
        except Exception as e:
            Constants.stopClient(f"initializeSocket Exception: {e}!")
    
    # sending socket with the right PACKET_SIZE
    def sendSocket(socket, buffer):
         bytes_size = len(buffer)
         if bytes_size < Constants.PACKET_SIZE:
            buffer += bytearray(Constants.PACKET_SIZE - bytes_size)
         elif bytes_size > Constants.PACKET_SIZE:
            buffer = buffer[:Constants.PACKET_SIZE]
         socket.send(buffer)
