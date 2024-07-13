#include <sys/stat.h>

int checkFileType(const char *path)
{
    struct stat stat1;

    if(lstat(path, &stat1) != 0){
        return -1;
    }

    if(S_ISREG(stat1.st_mode)){
        return S_IFREG;
    }
    if(S_ISDIR(stat1.st_mode)){
        return S_IFDIR;
    }
    if(S_ISCHR(stat1.st_mode)){
        return S_IFCHR;
    }
    if(S_ISBLK(stat1.st_mode)){
        return S_IFBLK;
    }
    if(S_ISFIFO(stat1.st_mode)){
        return S_IFIFO;
    }
    if(S_ISLNK(stat1.st_mode)){
        return S_IFLNK;
    }
    if(S_ISSOCK(stat1.st_mode)){
        return S_IFSOCK;
    }

    return -1;
}
