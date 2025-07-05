#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include "../file/fileListing.h"
#include "../flags/flags.h"

extern uint32_t app_flags;


int compare_filetype_and_name(const void *a, const void *b){
    const struct fileListing *fa = (const struct fileListing *)a;
    const struct fileListing *fb = (const struct fileListing *)b;

    mode_t type_a = fa->st.st_mode & S_IFMT;
    mode_t type_b = fa->st.st_mode & S_IFMT;

    if(type_a != type_b){
        if(type_a > type_b){
            return 1;
        } else if (type_a < type_b){
            return -1;
        } else{
            return 0;
        }
    }

    //return strcmp(fa->name, fb->name);
    return strcmp(fa->path, fb->path);

}


int compare_filetype_and_name_reverse(const void *a, const void *b){
    const struct fileListing *fa = (const struct fileListing *)a;
    const struct fileListing *fb = (const struct fileListing *)b;

    mode_t type_a = fa->st.st_mode & S_IFMT;
    mode_t type_b = fa->st.st_mode & S_IFMT;

    if(type_a != type_b){
        if(type_a > type_b){
            return -1;
        } else if (type_a < type_b){
            return 1;
        } else{
            return 0;
        }
    }


    //swap fb's to reverse order
    return strcmp(fb->path, fa->path);

}


int compare_time_and_filetype_and_name(const void *a, const void *b){

    const struct fileListing *fa = (const struct fileListing *)a;
    const struct fileListing *fb = (const struct fileListing *)b;


    if(app_flags & c_FLAG){
        if (fa->st.st_ctim.tv_sec != fb->st.st_ctim.tv_sec){

            if(fa->st.st_ctim.tv_sec > fb->st.st_ctim.tv_sec){
                return -1;
            } else if (fa->st.st_ctim.tv_sec < fb->st.st_ctim.tv_sec){
                return 1;
            }
        }
    }else if(app_flags & u_FLAG){
        if (fa->st.st_atim.tv_sec != fb->st.st_atim.tv_sec){

            if(fa->st.st_atim.tv_sec > fb->st.st_atim.tv_sec){
                return -1;
            } else if (fa->st.st_atim.tv_sec < fb->st.st_atim.tv_sec){
                return 1;
            }
        }
    } else{
        if (fa->st.st_mtim.tv_sec != fb->st.st_mtim.tv_sec){

            if(fa->st.st_mtim.tv_sec > fb->st.st_mtim.tv_sec){
                return -1;
            } else if (fa->st.st_mtim.tv_sec < fb->st.st_mtim.tv_sec){
                return 1;
            }
        }
    }




    mode_t type_a = fa->st.st_mode & S_IFMT;
    mode_t type_b = fa->st.st_mode & S_IFMT;

    if(type_a != type_b){
        if(type_a > type_b){
            return 1;
        } else if (type_a < type_b){
            return -1;
        } else{
            return 0;
        }
    }

    //return strcmp(fa->name, fb->name);
    return strcmp(fa->path, fb->path);
}

int compare_time_and_filetype_and_name_reverse(const void *a, const void *b){

    const struct fileListing *fa = (const struct fileListing *)a;
    const struct fileListing *fb = (const struct fileListing *)b;


    if(app_flags & c_FLAG){
        if (fa->st.st_ctim.tv_sec != fb->st.st_ctim.tv_sec){

            if(fa->st.st_ctim.tv_sec > fb->st.st_ctim.tv_sec){
                return 1;
            } else if (fa->st.st_ctim.tv_sec < fb->st.st_ctim.tv_sec){
                return -1;
            }
        }
    }else if(app_flags & u_FLAG){
        if (fa->st.st_atim.tv_sec != fb->st.st_atim.tv_sec){

            if(fa->st.st_atim.tv_sec > fb->st.st_atim.tv_sec){
                return 1;
            } else if (fa->st.st_atim.tv_sec < fb->st.st_atim.tv_sec){
                return -1;
            }
        }
    } else{
        if (fa->st.st_mtim.tv_sec != fb->st.st_mtim.tv_sec){

            if(fa->st.st_mtim.tv_sec > fb->st.st_mtim.tv_sec){
                return 1;
            } else if (fa->st.st_mtim.tv_sec < fb->st.st_mtim.tv_sec){
                return -1;
            }
        }
    }




    mode_t type_a = fa->st.st_mode & S_IFMT;
    mode_t type_b = fa->st.st_mode & S_IFMT;

    if(type_a != type_b){
        if(type_a > type_b){
            return -1;
        } else if (type_a < type_b){
            return 1;
        } else{
            return 0;
        }
    }

    //swap fb's to reverse order
    return strcmp(fb->path, fa->path);
}


int compare_file_size(const void *a, const void *b){
    const struct fileListing *fa = (const struct fileListing *)a;
    const struct fileListing *fb = (const struct fileListing *)b;
    if (fa->st.st_size < fb->st.st_size){
        return 1;
    } else if(fa->st.st_size > fb->st.st_size){
        return -1;
    } else{
        return 0;
    }
}

int compare_file_size_reverse(const void *a, const void *b){
    const struct fileListing *fa = (const struct fileListing *)a;
    const struct fileListing *fb = (const struct fileListing *)b;

    if (fa->st.st_size < fb->st.st_size){
        return -1;
    } else if(fa->st.st_size > fb->st.st_size){
        return 1;
    } else{
        return 0;
    }
}


int sortArray(struct fileListing **fl_arr, int file_count) {

    if(app_flags & f_FLAG){
        return 0;
    }

    if(app_flags & r_FLAG){
        if(app_flags & S_FLAG){
            qsort(*fl_arr, file_count, sizeof(struct fileListing), compare_file_size_reverse);
        } else if(app_flags & t_FLAG){
            qsort(*fl_arr, file_count, sizeof(struct fileListing), compare_time_and_filetype_and_name_reverse);
        } else{
            qsort(*fl_arr, file_count, sizeof(struct fileListing), compare_filetype_and_name_reverse);
        }
    }else{
        if(app_flags & S_FLAG){
            qsort(*fl_arr, file_count, sizeof(struct fileListing), compare_file_size);
        } else if(app_flags & t_FLAG){
            qsort(*fl_arr, file_count, sizeof(struct fileListing), compare_time_and_filetype_and_name);
        } else{
            qsort(*fl_arr, file_count, sizeof(struct fileListing), compare_filetype_and_name);
        }
    }

    return 0;
}
