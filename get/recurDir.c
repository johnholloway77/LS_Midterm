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
#include "../get/getFile.h"
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

    struct fileListing *dir_fl_arr = malloc(sizeof(struct fileListing));;
    int file_count = 0;

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

        // if (!(app_flags & A_FLAG) && !(app_flags & a_FLAG)) {
        //     if(node->fts_path[2] == '.'){
        //         break;
        //     }
        // }
        /*
            if (getFile(node->fts_path, &dir_fl_arr, &file_count) != 0) {
                perror("error getting file");
            }



            printf("node: %s\n", node->fts_path);
            */
        switch (node->fts_info) {
        case FTS_D:
            subdir_count++;

            if(app_flags & a_FLAG){
                // get_dot_dirs(node->fts_path, &dir_fl_arr, &file_count);
            }

            if((app_flags & R_FLAG)){


                if (is_new_directory) {
                    printf("\n"); // Line break before listing a new directory's contents
                }
                printf("Directory: %s\n", node->fts_path);
                //print_special_directories(node->fts_path);
                //get_dot_dirs(node->fts_path, &dir_fl_arr, &file_count);


                char *dirName = node->fts_path;
                printf("name: %s\n", dirName);
                printf("name + 2: %s\n", dirName + 2);

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

    sortArray(&dir_fl_arr, file_count);

    printListing(dir_fl_arr, file_count);
    free(dir_fl_arr);

    if (fts_close(file_system) < 0) {
        perror("fts_close");
        exit(EXIT_FAILURE);
    }


    return 0;
}
