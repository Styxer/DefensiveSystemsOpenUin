import random

class Constants:
    MAX_NAME_LEN = 256  # max filename len
    PACKET_SIZE = 1024
    CLIENT_VERSION = 1
    SERVER_INFO = "server.info"
    BACKUP_INFO = "backup.info" 
   

    @staticmethod
    def getUserID():
        max_uint32 = 0xFFFFFFFF
        return random.randint(1, max_uint32)

    @staticmethod
    def stopClient(err):  
        print("\nError:Fatal Error!", err, "Script execution will stop.", sep="\n")
        exit(1)
        

    

    
    
    
   
    