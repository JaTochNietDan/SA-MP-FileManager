//----------------------------------------------------------
//
//   FileManager v1.4 by JaTochNietDan
//	 http://www.jatochnietdan.com
//
//----------------------------------------------------------
#if defined(_WIN32)
	#include <io.h>   // For access().
	#include <direct.h>   // For access().
	#include "dirent.h"
#else
	#include <dirent.h>
#endif 

#include <sys/types.h>  // For stat().
#include <sys/stat.h>   // For stat().
#include <stdio.h> // for the sprintf function
#include "stdlib.h"
#include "malloc.h"
#include <string>
#include <fstream>
#include <cstring>


#include "SDK/amx/amx.h"
#include "SDK/plugincommon.h"

#define VERSION "Version 1.5"

using namespace std;
//----------------------------------------------------------
typedef void (*logprintf_t)(char* format, ...);

logprintf_t logprintf;
void **ppPluginData;
extern void *pAMXFunctions;

bool Logging = false;
//----------------------------------------------------------
PLUGIN_EXPORT unsigned int PLUGIN_CALL Supports() 
{
	return SUPPORTS_VERSION | SUPPORTS_AMX_NATIVES;
}

PLUGIN_EXPORT bool PLUGIN_CALL Load( void **ppData ) 
{
	pAMXFunctions = ppData[PLUGIN_DATA_AMX_EXPORTS];
	logprintf = (logprintf_t)ppData[PLUGIN_DATA_LOGPRINTF];

	logprintf( "******************" );
	logprintf( "** FILE MANAGER **" );
	logprintf( "**    Loaded    **" );
	logprintf( "** %s **",VERSION);
	logprintf( "******************" );
	return true;
}

PLUGIN_EXPORT void PLUGIN_CALL Unload( )
{
	if(Logging) logprintf( "[FileManager]: FileManager was unloaded." );
}

static cell AMX_NATIVE_CALL n_file_move( AMX* amx, cell* params )
{
	char *file;
	char *destination;

	amx_StrParam(amx, params[1], file);
	amx_StrParam(amx, params[2], destination);

	if(rename(file,destination) != -1)
	{
		if(Logging) logprintf("[FileManager]: The file \"%s\" was moved to \"%s\"",file,destination);
		return true;
	}
	if(Logging) logprintf("[FileManager]: The file \"%s\" could not be moved to \"%s\"",file,destination);
	return false;
}

static cell AMX_NATIVE_CALL n_file_delete( AMX* amx, cell* params )
{
	char *file;

	amx_StrParam(amx, params[1], file);

	if(remove(file) != -1)
	{
		if(Logging) logprintf("[FileManager]: The file \"%s\" was deleted",file);
		return true;
	}
	if(Logging) logprintf("[FileManager]: The file \"%s\" could not be deleted",file);
	return false;
}

static cell AMX_NATIVE_CALL n_file_create( AMX* amx, cell* params )
{
	char *file;

	amx_StrParam(amx, params[1], file);

	FILE *pFile = fopen(file,"w");
	if(pFile)
	{
		if(Logging) logprintf("[FileManager]: \"%s\" was created succesfully",file);
		fclose(pFile);
		return true;
	}
	else
	if(Logging) logprintf("[FileManager]: \"%s\" was not created succesfully",file);
	return false;
}

static cell AMX_NATIVE_CALL n_file_write( AMX* amx, cell* params )
{
	char
		*file,
		*text,
		*mode;

	amx_StrParam(amx, params[1], file);
	amx_StrParam(amx, params[2], text);
	amx_StrParam(amx, params[3], mode);

	FILE *pFile = fopen(file,mode);
	if(pFile)
	{
		fwrite(text,1,strlen(text),pFile);
		if(Logging) logprintf("[FileManager]: \"%s\" was written to succesfully in \"%s\" mode!",file,mode);
		fclose(pFile);
		return true;
	}
	if(Logging) logprintf("[FileManager]: \"%s\" was not written to succesfully in \"%s\" mode!",file,mode);
	return false;
}

static cell AMX_NATIVE_CALL n_file_read( AMX* amx, cell* params )
{
	char 
		*file,
		*buffer;

	long lSize;
	cell *buf;

	bool success = false;

	amx_StrParam(amx, params[1], file);

	FILE *pFile = fopen(file,"r");
	if(pFile)
	{
		fseek (pFile , 0 , SEEK_END);
		lSize = ftell (pFile);
		rewind (pFile);

		if((lSize + 2) > params[3]) lSize = params[3]; // Users array is smaller than read data, only store as much as they specified

		if((buffer = (char*) malloc (sizeof(char)* (lSize + 2))) != NULL) // Check memory is allocated correctly
		{
			fread (buffer, lSize, 1, pFile);

			amx_GetAddr(amx, params[2], &buf);

			buffer[lSize + 1] = NULL;

			amx_SetString(buf, buffer, 0, 0, lSize + 1);

			free(buffer); // Free allocated memory, otherwise we get a memory leak

			if(Logging) logprintf("[FileManager]: \"%s\" was read succesfully",file);
			success = true;
		}
		fclose(pFile);	
	}
	if(Logging && !success) logprintf("[FileManager]: \"%s\" was not read succesfully",file);
	return success;
}

static cell AMX_NATIVE_CALL n_file_copy( AMX *amx, cell *params)
{
	char
		*file,
		*filedest;

	amx_StrParam(amx, params[1], file);
	amx_StrParam(amx, params[2], filedest);

	FILE *pFile = fopen(file,"r");
	if(pFile)
	{
		fclose(pFile);
		
		ifstream f1(file, fstream::binary);
		ofstream f2(filedest, fstream::trunc|fstream::binary);

		if(f2 << f1.rdbuf()) return true;
	}
	return false;
}

static cell AMX_NATIVE_CALL n_dir_create( AMX* amx, cell* params )
{
	char *dir;

	amx_StrParam(amx, params[1], dir);
#if defined(_WIN32)
	if(mkdir(dir) == -1)
	{
		if(Logging) logprintf("[FileManager]: Directory \"%s\" could not be created!",dir);
		return false;
	}
#else 
	if(mkdir(dir,0755) == -1)
	{
		if(Logging) logprintf("[FileManager]: Directory \"%s\" could not be created!",dir);
		return false;
	}
#endif
	if(Logging) logprintf("[FileManager]: Directory \"%s\" was created!",dir);
	return true;
}

static cell AMX_NATIVE_CALL n_dir_delete( AMX* amx, cell* params )
{
	char *dir;

	amx_StrParam(amx, params[1], dir);

	if(rmdir(dir) != 0)
	{
		if(Logging) logprintf("[FileManager]: Directory \"%s\" could not be deleted!",dir);
		return false;
	}
	if(Logging) logprintf("[FileManager]: Directory \"%s\" was deleted!",dir);
	return true;
}

#if defined(_WIN32)

static cell AMX_NATIVE_CALL n_dir_exists(AMX* amx, cell* params)
{
	char *dir;
	string strPath;

	amx_StrParam(amx, params[1],dir);

	strPath.append(dir);

    if ( access( strPath.c_str(), 0 ) == 0 )
    {
        struct stat status;
        stat( strPath.c_str(), &status );

        if ( status.st_mode & S_IFDIR )
        {
			if(Logging) logprintf("[FileManager]: Directory \"%s\" exists!",dir);
            return 1;
        }
        else
        {
			if(Logging) logprintf("[FileManager]: Directory \"%s\" is not a directory, it's a file!",dir);
            return 2;
        }
    }
    else
    {
		if(Logging) logprintf("[FileManager]: Directory \"%s\" does not exist!",dir);
        return 0;
    }
}

#else

static cell AMX_NATIVE_CALL n_dir_exists(AMX* amx, cell* params)
{
    struct stat st;
	char *dir;

	amx_StrParam(amx, params[1],dir);

    if (stat(dir,&st) == 0)
    {
		if(Logging) logprintf("[FileManager]: Directory \"%s\" exists!",dir);
        return true;
	}
	if(Logging) logprintf("[FileManager]: Directory \"%s\" does not exist!",dir);
    return false;
}

#endif

static cell AMX_NATIVE_CALL n_file_exists( AMX* amx, cell* params)
{
	char* file;
	
	amx_StrParam(amx,params[1],file);

	FILE *pFile = fopen(file,"r");
	if(pFile)
	{
		fclose(pFile);
		return true;
	}
	return false;
}

static cell AMX_NATIVE_CALL n_f_open( AMX* amx, cell* params)
{
	char *file, *mode;
	
	amx_StrParam(amx, params[1], file);
	amx_StrParam(amx, params[2], mode);
	
	return (cell)fopen(file, mode); // Return the file handle as a cell
}

static cell AMX_NATIVE_CALL n_f_close( AMX* amx, cell* params)
{
	FILE *pFile = (FILE*)params[1]; // Define the file handle as the first parameter

	if(pFile) 
	{
		fclose(pFile);
		return true;
	}
	return false;
}

static cell AMX_NATIVE_CALL n_dir_open( AMX* amx, cell* params)
{
	char* path;
	DIR* dir;

	amx_StrParam(amx, params[1], path);

	dir = opendir (path);
    if (dir != NULL) return (cell)dir;
	return 0;
}

static cell AMX_NATIVE_CALL n_dir_list( AMX* amx, cell* params)
{
	DIR *dir = (DIR*)params[1];
	
	struct dirent *ent;

	if ((ent = readdir (dir)) != NULL) 
	{
		cell *buf, *addr;

		amx_GetAddr(amx, params[3], &addr);

		switch (ent->d_type) 
		{
			case DT_REG:
				*addr = 2;
				break;
			case DT_DIR:
				*addr = 1;
				break;
			default:
				*addr = 0;
        }
		
		amx_GetAddr(amx, params[2], &buf);

		amx_SetString(buf, ent->d_name, 0, 0, params[4]);
		return true;
	}
	return false;
}

static cell AMX_NATIVE_CALL n_dir_close( AMX* amx, cell* params)
{
	DIR *dir = (DIR*)params[1];
	closedir (dir);
	return true;
}

static cell AMX_NATIVE_CALL n_f_read( AMX* amx, cell* params)
{
	FILE *pFile = (FILE*)params[1]; // Define the file handle as the first parameter
	
	char *buffer;

	cell *buf;


	if(pFile) // Is it a valid file handle?
	{
		if((buffer = (char*) malloc (sizeof(char) * params[3])) != NULL) // Check memory is allocated correctly
		{
			if(fgets(buffer, params[3], pFile) != NULL) // Get the current line, will return NULL if no more lines
			{
				int index = strlen(buffer) - 1; // Get the last cell index

				if(buffer[index] == '\n') // Check if the last cell contains a newline
					buffer[index] = 0; // Remove it

				amx_GetAddr(amx, params[2], &buf);

				amx_SetString(buf, buffer, 0, 0, params[3]);
				
				free(buffer); // Need to free the buffer, otherwise it's a memory leak!
				return true;
			}
		}
	}
	return false;
}

static cell AMX_NATIVE_CALL n_f_write( AMX* amx, cell* params)
{
	FILE *pFile = (FILE*)params[1]; // Define the file handle as the first parameter

	if(pFile) // Is it a valid file handle?
	{
		char *buf;

		amx_StrParam(amx, params[2], buf);

		fwrite(buf, 1, strlen(buf), pFile); // Write to the file
		return true;
	}
	return false;
}

static cell AMX_NATIVE_CALL n_file_log( AMX* amx, cell* params )
{
	Logging = 1;
	logprintf("[FileManager]: Logging started!");
	return false;
}

AMX_NATIVE_INFO FileManagerNatives[ ] =
{
	{ "file_move",		n_file_move		},
	{ "file_delete",	n_file_delete	},
	{ "file_create",	n_file_create	},
	{ "file_write",		n_file_write	},
	{ "file_read",		n_file_read		},
	{ "file_log",		n_file_log		},
	{ "file_exists",	n_file_exists	},
	{ "file_copy",		n_file_copy		},

	{ "dir_create",		n_dir_create	},
	{ "dir_delete",		n_dir_delete	},
	{ "dir_exists",		n_dir_exists	},

	{ "dir_open",		n_dir_open		},
	{ "dir_close",		n_dir_close		},
	{ "dir_list",		n_dir_list		},

	{ "f_open",			n_f_open		},
	{ "f_close",		n_f_close		},
	{ "f_read",			n_f_read		},
	{ "f_write",		n_f_write		},

	{ 0,				0				}
};

PLUGIN_EXPORT int PLUGIN_CALL AmxLoad( AMX *amx ) 
{
	return amx_Register( amx, FileManagerNatives, -1 );
}

PLUGIN_EXPORT int PLUGIN_CALL AmxUnload( AMX *amx ) 
{
	return AMX_ERR_NONE;
}
