#include <sys/stat.h>
#include <stdlib.h>


char *strFileMode(struct stat stat)
{
    char *modeString = (char*)malloc(sizeof(char)* 11);
    modeString[10] = '\0';


    //Set the file type to first char
    if(S_ISREG(stat.st_mode)){
        modeString[0] = '-';
    }
    else if (S_ISBLK(stat.st_mode)){
        modeString[0] = 'b';
    }
    else if(S_ISCHR(stat.st_mode)){
        modeString[0] = 'c';
    }
    else if(S_ISDIR(stat.st_mode)){
        modeString[0] = 'd';
    }
    else if(S_ISLNK(stat.st_mode)){
        modeString[0] = 'l';
    }
    else if(S_ISSOCK(stat.st_mode)){
        modeString[0] = 's';
    }
    else if(S_ISFIFO(stat.st_mode)){
        modeString[0] = 'p';
    }
    else if(S_ISWHT(stat.st_mode)){
        modeString[0] = 'w';
    }

    /*
     *
     * You need to get the remaining file types entered: Archive state 1, Archiev state 2, and Whiteout!!!
     */


    //Set the next three chars for the owner permissions.


    modeString[1] = (stat.st_mode & S_IRUSR) ? 'r' : '-';
    modeString[2] = (stat.st_mode & S_IWUSR) ? 'w' : '-';
    if(stat.st_mode & S_IXUSR){
        if(stat.st_mode & S_ISUID){
            modeString[3] = 's';
        } else{
            modeString[3] = 'x';
        }
    } else if(stat.st_mode & S_ISUID){
        modeString[3] = 'S';
    } else{
        modeString[3] = '-';
    }


    //set the middle three chars for the group permissions
    modeString[4] = (stat.st_mode & S_IRGRP) ? 'r' : '-';
    modeString[5] = (stat.st_mode & S_IWGRP) ? 'w' : '-';
    if(stat.st_mode & S_IXGRP){
        if(stat.st_mode & S_ISGID){
            modeString[6] = 's';
        } else{
            modeString[6] = 'x';
        }
    } else if(stat.st_mode & S_ISGID){
        modeString[6] = 'S';
    } else{
        modeString[6] = '-';
    }

    //set the last three chars for the other permissions
    modeString[7] = (stat.st_mode & S_IROTH) ? 'r' : '-';
    modeString[8] = (stat.st_mode & S_IWOTH) ? 'w' : '-';
    if(stat.st_mode & S_IXOTH){
        if(stat.st_mode & S_ISGID){
            modeString[9] = 't';
        } else{
            modeString[9] = 'x';
        }
    } else if(stat.st_mode & S_ISVTX){
        modeString[9] = 'T';
    } else{
        modeString[9] = '-';
    }

    return modeString;
}
