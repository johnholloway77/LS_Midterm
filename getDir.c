#include <fts.h>
#include <sys/limits.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>

#include "./fileListing.h"
#include "./flags.h"
#include "./getFile.h"

extern uint32_t app_flags;
extern struct stat *statv;
extern int statCount;

void print_special_directories(const char *path) {
    printf("File: %s/.\n", path);
    printf("File: %s/..\n", path);
}

int getDir(char *path) {

    struct fileListing *dir_fl_arr;
    int file_count;

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

            if(!(app_flags & S_FLAG)){
                if(node->fts_level > 1) continue;
            }

            switch (node->fts_info) {
            case FTS_D:
                subdir_count++;
                //printf("Directory: %s\n", node->fts_path);
                if((app_flags & S_FLAG)){


                    if (is_new_directory) {
                        printf("\n"); // Line break before listing a new directory's contents
                    }
                    printf("Directory: %s\n", node->fts_path);
                    print_special_directories(node->fts_path);
                    is_new_directory = 1;
                    break;
                }
            case FTS_F:
                printf("File: %s\n", node->fts_path);
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

/*
 * Fancy printing thingimajig
 */
// double result = (double)count / 5;
// rowcount = (int)ceil(result);

// for (int i = 0; i < count; i++) {
//   for (int j = i + 1; j < count; j++) {
//     if (strcmp(entries[i], entries[j]) > 0) {
//       char *temp = entries[i];
//       entries[i] = entries[j];
//       entries[j] = temp;
//     }
//   }
// }

// for (int r = 0; r < rowcount; r++) {
//   for (int c = 0; c < 5; c++) {
//     int array_index = c * rowcount + r;

//     if (array_index < count) {
//       printf("%-16s\t", entries[array_index]);
//     }
//   }
//   printf("\n");
// }
