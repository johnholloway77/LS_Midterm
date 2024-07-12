#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>


#include "./flags.h"
extern uint32_t app_flags;

int countDirectoryEntries(char *path)
{
    DIR *d_ptr;
    struct dirent *dir_ptr;
    int entry_count = 0;

    if((d_ptr = opendir(path)) == NULL){
        fprintf(stderr, "Unable to open %s: %s\n", path, strerror(errno));
        return -1;
    }

    while((dir_ptr = readdir(d_ptr)) != NULL){

        if(!(app_flags & a_FLAG)){

            if(strcmp(dir_ptr->d_name, ".") != 0 && strcmp(dir_ptr->d_name, "..") != 0){
                if(dir_ptr->d_name[0] == '.') continue;
            }

        }

        if((strcmp(dir_ptr->d_name, ".") == 0 || strcmp(dir_ptr->d_name, "..") == 0) && !(app_flags & A_FLAG)) continue;

        entry_count++;
    }

    return entry_count;

}
