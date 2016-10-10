SA-MP-FileManager
=================

#### What is FileManager?
FileManager is a simple plugin which allows you to manage files and folders.

#### Can't you just use the standard PAWN API?
Unlike the standard SA-MP API you are not limited to the scriptfiles server directory with this plugin.

#### Functions Included

```pawn
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

#### Thanks to
- G-sTyLeZzZ (Coding support)
- Y_Less (Bug finding)
