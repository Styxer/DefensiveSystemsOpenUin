A simple file backup client-server program
Uses Boost and c++ on the server side
Client uses python3 and standart socket

in order this to work you need to create 2 files

1.backup.info
	Location - same place a "Maman14Client.py"( "main" function)
	Content - {IP}:{Port} [for example 127.0.0.1:8080]
	IMPORTANT - if you change the port here change the port in "Maman14Server"(there was no request that the server will read the port name from the files)

2.backup.ifno
	Location - same place a "Maman14Client.py"( "main" function)
	Content - list of the file name without a path, each file in a new line
		[For eaxmple :
			maman14Client.py
			Op.py
			Status.py]

-Request Files List
 request files list from the user backupfolder
 returns the list of the files from the server 
 returns error if file list is empty

-Request File Backup
 params - file name from backup.info
 request a file to backup in user folder, creates one, if no such folder exists
 returns error if the file name does not exist in backup.info or if backup failed

-Request File Restore
 params - file name from backup.info, a name of the file where the backup will be saved
 request a file to back up from the user backup folder
 returns error if file does not exist in backup.info or it does not exits in user backup folder or restore failed

-Request File Removal
 params - file name from backup.info, a name of the file to remove
 request a file to remove from the user backup folder
  returns error if file does not exist in backup.info or it does not exits in user backup folder or remove failed

 

