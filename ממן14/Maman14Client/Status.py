from enum import Enum

# Response Codes
class Status(Enum):
      SUCCESS_RESTORE = 210  # File was found and restored. all fields are valid.
      SUCCESS_DIR = 211  # Files listing returned successfully. all fields are valid.
      SUCCESS_BACKUP_REMOVE = 212  # File was successfully backed up or deleted. size, payload are invalid.
      ERROR_NOT_EXIST = 1001  # File doesn't exist. size, payload are invalid.
      ERROR_NO_FILES = 1002  # Client has no files. Only status & version are valid.
      ERROR_GENERIC = 1003  # Generic server error. Only status & version are valid.