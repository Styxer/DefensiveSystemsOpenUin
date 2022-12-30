#pragma once
enum OPEnum
{
	FILE_BACKUP = 100, //save file for backup, all field should be filled and valid
	FILE_RESTORE = 200,//resote a file. size and paylod are not in use
	FILE_REMOVE = 201, //delete a file. size and paylod are not in use
	FILE_DIR = 202,    //list al clients files.
};
