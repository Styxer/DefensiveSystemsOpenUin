#pragma once
enum StatusEnum {

	SUCCESS_RESTORE = 210,		//file was found and restored. all field are used and valid
	SUCCESS_DIR = 211,		    //files listing reurned successfully. all field are used and valid
	ERROR_NOT_EXIST = 1001,		//file dose not exist. soze and payload does not exit
	ERROR_NO_FILES = 1002,	    //client has not files. only status and version are used and valid.
	ERROR_GENERIC = 1003,        //generic server error. only status and version are used and valid
	SUCCESS_BACKUP_DELETE = 212,   // MY OWN ADDITION -  File was successfully backed up or deleted. size, payload are invalid.
};
