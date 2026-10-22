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
native dir:dir_open_sorted(const directory[]);
native dir_close(dir:handle);
native dir_list(dir:handle, storage[], &type, length = sizeof(storage));
```

*Note: f_open is only needed for f_close and f_read, [b]none[/b] of the file_ functions require f_open*

*Note: Similarly, dir_open is only need for dir_close and dir_list, it is not needed for the rest of the dir functions*

#### Quick Examples

**Listing a directory**

```pawn
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

#### Sorted directory listings

For consistent alphabetical ordering on Windows and Linux, replace `dir_open`
with `dir_open_sorted`. Continue using `dir_list` and `dir_close` as above.
The new function takes a snapshot at open time and sorts names in case-sensitive
byte order (uppercase before lowercase), independent of the system locale.
Files and directories are sorted together; `.` and `..` are included when the
filesystem supplies them. Changes made after opening are not reflected in the
snapshot. It returns `0` if the directory cannot be opened or read.
The existing `dir_open` continues to use filesystem order.

#### Building and releases

Install [mise](https://mise.jdx.dev/), then run from the repository root:

```sh
mise trust
mise install
mise run test
mise run build
```

The pinned Zig toolchain cross-compiles both 32-bit SA-MP plugins without a
separate compiler or multilib installation. Host tests on macOS use the existing
Xcode Command Line Tools compiler. Python packages the binaries,
include, example, README and license into `build/FileManager_dev_Linux.zip`
and `build/FileManager_dev_Windows.zip`. Linux targets glibc 2.17 or newer.
To build just one platform, use
`mise exec -- python scripts/build.py --platform Linux` (or `Windows`).

GitHub Actions tests on Linux and Windows and uploads both archives for pull
requests and pushes to `master`. To publish a release, push a version tag such
as `v1.6.0`. Once both builds pass, the workflow publishes a GitHub Release
with `FileManager_v1.6.0_Linux.zip` and `FileManager_v1.6.0_Windows.zip`.
Manual workflow runs build downloadable artifacts without publishing a release.
