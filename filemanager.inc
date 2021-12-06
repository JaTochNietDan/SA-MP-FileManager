
#if defined _INC_file_manager
	#undef _INC_file_manager
#endif

#if defined _file_manager_included
	#endinput
#endif

#define _file_manager_included

// FM_DIR defines a directory and FM_FILE defines a file
// when using dir_list, these will be the types returned.
#define FM_DIR 1
#define FM_FILE 2

/*
	Function: file_move(const file[], const destination[]);
	Description: Moves a specified file to the specified destination.
	Params:
			const file[] - The name of the file to be moved.
			const destination[] - The destination to move the file to, including the file name.
			
	Returns: True if success, false if not.
*/
native file_move(const file[], const destination[]);

/*
	Function: file_copy(const file[], const destination[]);
	Description: Copies a specified file to the specified destination.
	Params:
			const file[] - The name of the file to be copied.
			const destination[] - The new destination of the file to be copied to, including the file name.
			
	Returns: True if success, false if not.
*/
native file_copy(const file[], const destination[]);

/*
	Function: file_delete(const file[]);
	Description: Deletes a specified file.
	Params:
			const file[] - The name of the file to be deleted.
			
	Returns: True if success, false if not.
*/
native file_delete(const file[]);

/*
	Function: file_create(const file[]);
	Description: Creates a specified file.
	Params:
			const file[] - The name of the file to be created.
			
	Returns: True if success, false if not.
*/
native file_create(const file[]);

/*
	Function: file_write(const file[], const text[], const mode[] = "a");
	Description: Writes a string to a specified file with the specified mode.
	Params:
			const file[] - The name of the file to be written to.
			const text[] - The string to write to the file.
			const mode[] - The mode to use (doesn't need to be specified, will append by default, can be set otherwise)
			
	Returns: True if success, false if not.
*/
native file_write(const file[], const text[], const mode[] = "a");

/*
	Function: file_read(const file[], const storage[], size = sizeof(storage));
	Description: Reads the entire file into a specified string.
	Params:
			const file[] - The name of the file to be read into memory.
			const storage[] - The array to store the read data in.
			const size[] - The size of the storage array (used to prevent buffer overflows), no reason for you to specify it in practice.
			
	Returns: True if success, false if not.
*/
native file_read(const file[], storage[], size = sizeof(storage));

/*
	Function: file_log();
	Description: Will enable filemanager logging (prints information about file operations).
*/
native file_log();

/*
	Function: file_exists(const file[]);
	Description: Checks if a specified file exists.
	Params:
			const file[] - The name of the file to be checked for existence.
			
	Returns: True if success, false if not.
*/
native file_exists(const file[]);

/*
	Function: f_open(const file[], const mode[] = "r");
	Description: Opens a file for a reading operation.
	Params:
			const file[] - The name of the file to be opened.
			const mode[] (Optional) - This can be used to set the mode, use "w" for write, "r" for read and "a" for append.
			
	Returns: The file handle if success, else it returns false.
*/
native File:f_open(const file[], const mode[] = "r"); 

/*
	Function: f_close(File: file);
	Description: Closes a file opened with f_open.
	Params:
			File:file - The handler of the file to be closed
	Returns: True if success, false if not.
*/
native f_close(File: file);

/*
	Function: f_read(File: file, const storage[], size = sizeof(storage));
	Description: Reads from file that was opened by f_open line by line.
	Params:
			File:file - The handler of the file to be read from.
			const storage[] - The string to store the read data from.
			size - This parameter does not need to be set by you.
			
	Returns: True if success, false if not.
*/
native f_read(File: file, storage[], size = sizeof(storage));

/*
	Function: f_write(File: file, const string[]);
	Description: Writes to a file that has been opened using f_open.
	Params:
			File:file - The handler of the file to be read from.
			const string[] - The string to write to the file.
			
	Returns: True if success, false if not.
*/
native f_write(File: file, const string[]);

/*
	Function: dir_create(const directory[]);
	Description: Creates a directory.
	Params:
			const directory[] - The path of the directory to be created.
			
	Returns: True if success, false if not.
*/
native dir_create(const directory[]);

/*
	Function: dir_delete(const directory[]);
	Description: Deletes a directory.
	Params:
			const directory[] - The path of the directory to be deleted.
			
	Returns: True if success, false if not.
*/
native dir_delete(const directory[]);

/*
	Function: dir_exists(const directory[]);
	Description: Checks if a directory exists
	Params:
			const directory[] - The path of the directory to be deleted.
			
	Returns: 1 if it exists, 2 if it is a file and 0 if it does not exist.
*/
native dir_exists(const directory[]);

/*
	Function: dir:dir_open(const directory[]);
	Description: Opens a directory
	Params:
			const directory[] - The path of the directory to be opened.
			
	Returns: 1 if it exists, and 0 if it does not exist.
*/
native dir:dir_open(const directory[]);

/*
	Function: dir_close(dir:handle);
	Description: Closes a directory
	Params:
			dir:handle - The handle of the directory to close that was previously opened.
			
	Returns: Nothing.
*/
native dir_close(dir:handle);

/*
	Function: dir_list(dir:handle, const storage[], &type, length = sizeof(storage));
	Description: Reads through a directory, listing each file/sub-directory one by one.
	Params:
			dir:handle - The handle of the directory that is open to read from.
			const storage[] - Where the name of the file/directory is stored.
			type - Where the type of directory is stored, can be either 1 or 2
			(optional) length - This is not needed unless you are passing an array without any length, in which case, use strlen with your array.
			
	Returns: 1 if there a sub-directory/file was found, 0 if there wasn't.
*/
native dir_list(dir:handle, storage[], &type, length = sizeof(storage));
