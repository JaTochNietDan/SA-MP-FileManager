SA-MP-FileManager
=================

#### What is FileManager?
FileManager is a simple plugin which allows you to manage files and folders.

#### Can't you just use the standard PAWN API?
Unlike the standard SA-MP API you are not limited to the scriptfiles server directory with this plugin.

#### Functions Included

```
native file_move(file[],destination[]); // Moves a file
native file_delete(file[]); // Deletes a file
native file_create(file[]); // Creates a file
native file_write(file[],text[],mode[] = "a"); // Writes in append mode to a file, option to set write mode, append mode is default
native file_read(file[],storage[], sizeof(storage)); // Saves to the specified string
native file_log(); // Adding this will enable logging
native file_exists(file[]); // Check if a file exists

native File:f_open(file[], mode[] = "r"); // Opens a file for line-by-line reading. a for append, w for write, r for read.
native f_close(File:file); // Closes a file that was opened by f_open.
native f_read(File:file, storage, sizeof(storage)); // Reads from a file opened by f_open, line by line.
native f_write(File:file, string[]); // Writes to a file that has been opened by f_open

native dir_create(directory[]); // Creates a new directory
native dir_delete(directory[]); // Deletes a directory (Directory MUST be empty!)
native dir_exists(directory[]); // Check if a directory exists

native dir:dir_open(directory[]);
native dir_close(dir:handle);
native dir_list(dir:handle, storage[], &type, length = sizeof(storage));
```

*Note: f_open is only needed for f_close and f_read, [b]none[/b] of the file_ functions require f_open*

*Note: Similarly, dir_open is only need for dir_close and dir_list, it is not needed for the rest of the dir functions*

#### Function Documentation

```
/*
	Function: file_move(file[], destination[]);
	Description: Moves a specified file to the specified destination.
	Params:
			file[] - The name of the file to be moved.
			destination[] - The destination to move the file to, including the file name.
			
	Returns: True if success, false if not.


	Function: file_copy(file[], destination[]);
	Description: Copies a specified file to the specified destination.
	Params:
			file[] - The name of the file to be copied.
			destination[] - The new destination of the file to be copied to, including the file name.
			
	Returns: True if success, false if not.


	Function: file_delete(file[]);
	Description: Deletes a specified file.
	Params:
			file[] - The name of the file to be deleted.
			
	Returns: True if success, false if not.


	Function: file_create(file[]);
	Description: Creates a specified file.
	Params:
			file[] - The name of the file to be created.
			
	Returns: True if success, false if not.


	Function: file_write(file[], text[], mode[] = "a");
	Description: Writes a string to a specified file with the specified mode.
	Params:
			file[] - The name of the file to be written to.
			text[] - The string to write to the file.
			mode[] - The mode to use (doesn't need to be specified, will append by default, can be set otherwise)
			
	Returns: True if success, false if not.


	Function: file_read(file[], storage[], size = sizeof(storage));
	Description: Reads the entire file into a specified string.
	Params:
			file[] - The name of the file to be read into memory.
			storage[] - The array to store the read data in.
			size[] - The size of the storage array (used to prevent buffer overflows), no reason for you to specify it in practice.
			
	Returns: True if success, false if not.


	Function: file_log();
	Description: Will enable filemanager logging (prints information about file operations).


	Function: file_exists(file[]);
	Description: Checks if a specified file exists.
	Params:
			file[] - The name of the file to be checked for existence.
			
	Returns: True if success, false if not.


	Function: f_open(file[], mode[] = "r");
	Description: Opens a file for a reading operation.
	Params:
			file[] - The name of the file to be opened.
			mode[] (optional) - Specifies to mode to open the file in. "a" is append, "w" is write, "r" is read
			
	Returns: The file handle if success, else it returns false.


	Function: f_close(File: file);
	Description: Closes a file opened with f_open.
	Params:
			File:file - The handler of the file to be closed

	Returns: True if success, false if not.


	Function: f_read(File: file, storage[], size = sizeof(storage));
	Description: Reads from file that was opened by f_open line by line.
	Params:
			File:file - The handler of the file to be read from.
			storage[] - The string to store the read data from.
			size - This parameter does not need to be set by you.
			
	Returns: True if success, false if not.

	Function: f_write(File: file, string[]);
	Description: Writes to a file that has been opened with f_open
	Params:
			File:file - The handler of the file to be read from.
			string[] - The string to write to the file.
			
	Returns: True if success, false if not.


	Function: dir_create(directory[]);
	Description: Creates a directory.
	Params:
			directory[] - The path of the directory to be created.
			
	Returns: True if success, false if not.


	Function: dir_delete(directory[]);
	Description: Deletes a directory.
	Params:
			directory[] - The path of the directory to be deleted.
			
	Returns: True if success, false if not.


	Function: dir_exists(directory[]);
	Description: Checks if a directory exists
	Params:
			directory[] - The path of the directory to be deleted.
			
	Returns: 1 if it exists, 2 if it is a file and 0 if it does not exist.


	Function: dir:dir_open(directory[]);
	Description: Opens a directory
	Params:
			directory[] - The path of the directory to be opened.
			
	Returns: 1 if it exists, and 0 if it does not exist.


	Function: dir_close(dir:handle);
	Description: Closes a directory
	Params:
			dir:handle - The handle of the directory to close that was previously opened.
			
	Returns: Nothing.


	Function: dir_list(dir:handle, storage[], &type, length = sizeof(storage));
	Description: Reads through a directory, listing each file/sub-directory one by one.
	Params:
			dir:handle - The handle of the directory that is open to read from.
			storage[] - Where the name of the file/directory is stored.
			type - Where the type of directory is stored, can be either 1 or 2
			(optional) length - This is not needed unless you are passing an array without any length, in which case, use strlen with your array.
			
	Returns: 1 if there a sub-directory/file was found, 0 if there wasn't.
*/

// FM_DIR defines a directory and FM_FILE defines a file
// when using dir_list, these will be the types returned.
#define FM_DIR 1
#define FM_FILE 2
```

#### Quick Examples

**Listing a directory**

```
new dir:dHandle = dir_open("./");
new item[40], type;
	
while(dir_list(dHandle, item, type))
{
    if(type == FM_FILE) printf("%s is a file", item);
    else if(type == FM_DIR) printf("%s is a directory", item);
}
		
dir_close(dHandle);
```

This will result in the contents of your SA-MP server directory being printed.

#### Supported Operating Systems
- Windows
- Linux

#### Download

http://www.jatochnietdan.com/project/sa-mp/filemanager

- Example Filterscript - http://pastebin.com/sqwFp9Xt

* Each download comes with the required include file for PAWN.*

**Thanks to**

G-sTyLeZzZ (Coding support)
Y_Less (Bug finding)
