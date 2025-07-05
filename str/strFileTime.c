#include <time.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include "../flags/flags.h"

extern uint32_t app_flags;
char *strFileTime(struct stat st)
{

    char *str_buf = (char *)malloc(sizeof(char) * 80);

    struct tm *local;

    if(app_flags & c_FLAG){
        local= localtime(&st.st_ctim.tv_sec);
    } else if(app_flags & u_FLAG){
        local = localtime(&st.st_atim.tv_sec);
    } else {
        local = localtime(&st.st_mtim.tv_sec);
    }


    strftime(str_buf, 80, "%b %d %H:%M", local);

    return  str_buf;
}
