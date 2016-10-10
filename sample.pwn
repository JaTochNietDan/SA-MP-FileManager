#include <a_samp>
#include <filemanager>
 
new command[3][120];
 
public OnFilterScriptInit()
{
        print("FileManager test filterscript has been loaded");
        return 1;
}
 
public OnRconCommand(cmd[])
{
        new idx;
 
        command[0] = strtok(cmd, idx);
 
        if(strcmp(command[0],"fwrite",true) == 0)
        {
                command[1] = strtok(cmd, idx);
                command[2] = strtok(cmd, idx);
               
                if(!strlen(command[1]) || !strlen(command[2]))
                {
                        print("[USAGE]: fwrite <file> <text>");
                        return 1;
                }
                       
                if(file_write(command[1],command[2])) printf("[SUCCESS]: '%s' has been written to '%s'",command[2],command[1]);
                else print("[FAIL]: The file could not be written!");
                return 1;
        }
        else if(strcmp(command[0],"fmove",true) == 0)
        {
                command[1] = strtok(cmd, idx);
                command[2] = strtok(cmd, idx);
               
                if(!strlen(command[1]) || !strlen(command[2]))
                {
                        print("[USAGE]: fmove <file> <newfile>");
                        return 1;
                }
               
                if(file_move(command[1],command[2])) print("[SUCCESS]: The file has been moved");
                else print("[FAIL]: The file did not move");
                return 1;
        }
        else if(strcmp(command[0],"fcopy",true) == 0)
        {
                command[1] = strtok(cmd, idx);
                command[2] = strtok(cmd, idx);
               
                if(!strlen(command[1]) || !strlen(command[2]))
                {
                        print("[USAGE]: fmove <file> <newfile>");
                        return 1;
                }
               
                if(file_copy(command[1],command[2])) print("[SUCCESS]: The file has been copied!");
                else print("[FAIL]: The file did not copy.");
                return 1;
        }
        else if(strcmp(command[0],"fdelete",true) == 0)
        {
                command[1] = strtok(cmd, idx);
 
                if(!strlen(command[1]))
                {
                        print("[USAGE]: fdelete <file>");
                        return 1;
                }
 
                if(file_delete(command[1])) print("[SUCCESS]: The file has been deleted");
                else print("[FAIL]: The file did not delete");
                return 1;
        }
        else if(strcmp(command[0],"fexists",true) == 0)
        {
                command[1] = strtok(cmd, idx);
 
                if(!strlen(command[1]))
                {
                        print("[USAGE]: fexists <file>");
                        return 1;
                }
 
                if(file_exists(command[1])) printf("[SUCCESS]: The file '%s' does exist",command[1]);
                else printf("[FAIL]: The file '%s' does not exist",command[1]);
                return 1;
        }
        else if(strcmp(command[0],"fread",true) == 0)
        {
                command[1] = strtok(cmd, idx);
 
                if(!strlen(command[1]))
                {
                        print("[USAGE]: fread <file>");
                        return 1;
                }
 
                if(file_read(command[1],command[2])) printf("[SUCCESS]: File '%s' contains '%s'",command[1],command[2]);
                else print("[FAIL]: The file could not be read");
                return 1;
        }
        else if(strcmp(command[0],"dcreate",true) == 0)
        {
                command[1] = strtok(cmd, idx);
 
                if(!strlen(command[1]))
                {
                        print("[USAGE]: dcreate <directory>");
                        return 1;
                }
 
                if(dir_create(command[1])) printf("[SUCCESS]: Directory '%s' created!",command[1]);
                else print("[FAIL]: The directory could not be created");
                return 1;
        }
        else if(strcmp(command[0],"ddelete",true) == 0)
        {
                command[1] = strtok(cmd, idx);
 
                if(!strlen(command[1]))
                {
                        print("[USAGE]: ddelete <directory>");
                        return 1;
                }
 
                if(dir_delete(command[1])) printf("[SUCCESS]: Directory '%s' deleted",command[1]);
                else print("[FAIL]: The directory could not be deleted, note, it needs to be empty!");
                return 1;
        }
        else if(strcmp(command[0],"dexists",true) == 0)
        {
                command[1] = strtok(cmd, idx);
 
                if(!strlen(command[1]))
                {
                        print("[USAGE]: dexists <directory>");
                        return 1;
                }
 
                if(dir_exists(command[1])) printf("[SUCCESS]: Directory '%s' exists!",command[1]);
                else print("[FAIL]: The directory does not exist!");
                return 1;
        }
        return 1;
}
 
strtok(const string[], &index)
{
        new length = strlen(string);
        while ((index < length) && (string[index] <= ' '))
        {
                index++;
        }
 
        new offset = index;
        new result[20];
        while ((index < length) && (string[index] > ' ') && ((index - offset) < (sizeof(result) - 1)))
        {
                result[index - offset] = string[index];
                index++;
        }
        result[index - offset] = EOS;
        return result;
}
