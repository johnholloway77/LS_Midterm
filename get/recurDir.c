#include <fts.h>
#include <string.h>
#include <sys/limits.h>
#include <sys/stat.h>
#include <sys/syslimits.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>

#include "../file//fileListing.h"
#include "../flags/flags.h"
#include "../get/getDir.h"
#include "../sort/sortArray.h"
#include "../print/printListing.h"

extern uint32_t app_flags;
extern struct stat *statv;
extern int statCount;

void print_special_directories(const char *path) {
    printf("File: %s/.\n", path);
    printf("File: %s/..\n", path);

}


int recurDir(char *path) {



    char *paths[] = {path, NULL};


    FTS *file_system = fts_open(paths, FTS_SEEDOT | FTS_NOCHDIR | FTS_PHYSICAL, NULL);
    if (!file_system) {
        perror("fts_open");
        exit(EXIT_FAILURE);
    }

    FTSENT *node;
    int is_new_directory = 0;
    int subdir_count = 0;

    while ((node = fts_read(file_system)) != NULL) {

        if(!(app_flags & R_FLAG)){
            if(node->fts_level > 1) continue;
        }

        switch (node->fts_info) {
        case FTS_D:

            if(app_flags & a_FLAG){
                // get_dot_dirs(node->fts_path, &dir_fl_arr, &file_count);
            }

            if((app_flags & R_FLAG)){

                char *dirName = node->fts_path;
                dirName += 2; //increase pointer to move forward 2 char

                if (is_new_directory) {
                    printf("\n");
                }
                printf("Directory: %s\n", dirName);
                //print_special_directories(node->fts_path);
                //get_dot_dirs(node->fts_path, &dir_fl_arr, &file_count);

                struct fileListing *dir_fl_arr = malloc(sizeof(struct fileListing));;
                int file_count = 0;

                getDir(dirName, &dir_fl_arr, &file_count);

                sortArray(&dir_fl_arr, file_count);

                printListing(dir_fl_arr, file_count);
                free(dir_fl_arr);

                is_new_directory = 1;
                break;
            }
        case FTS_F:
            if (!(app_flags & A_FLAG) && !(app_flags & a_FLAG)) {
                if(node->fts_path[2] == '.'){
                    break;
                }
            }

            //if (getFile(node->fts_path, &dir_fl_arr, &file_count) != 0) {
            //        perror("error getting file");
            //    }

            break;
        case FTS_DNR:
            fprintf(stderr, "Cannot read directory: %s\n", node->fts_path);
            break;
        case FTS_ERR:
            perror("fts_read");
            break;
        default:
            break;
        }


    }



    if (fts_close(file_system) < 0) {
        perror("fts_close");
        exit(EXIT_FAILURE);
    }


    return 0;
}
