#include <dirent.h>
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/limits.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "../file/fileListing.h"
#include "../flags/flags.h"
#include "../get/getFile.h"

extern uint32_t app_flags;
extern struct stat *statv;
extern int statCount;

int getDir(const char *path, struct fileListing **fl_arr, int *file_count) {
    DIR *d_ptr;
    struct dirent *dir_ptr;
    char file_path[PATH_MAX];

    if ((d_ptr = opendir(path)) == NULL) {
        fprintf(stderr, "Unable to open %s: %s\n", path, strerror(errno));
        return -1;
    }

    while ((dir_ptr = readdir(d_ptr)) != NULL) {


        // Skip hidden files unless either a_FLAG A_FLAG is set
        if ((!(app_flags & A_FLAG) && dir_ptr->d_name[0] == '.') && (!(app_flags & a_FLAG) && dir_ptr->d_name[0] == '.') ){
            continue;
        }


        // Skip "." and ".." unless a_FLAG is set
        if (!(app_flags & a_FLAG)) {
            if (strcmp(dir_ptr->d_name, ".") == 0 || strcmp(dir_ptr->d_name, "..") == 0)
                continue;
        }


        snprintf(file_path, PATH_MAX, "%s/%s", path, dir_ptr->d_name);

        if (getFile(file_path, fl_arr, file_count) != 0) {
            perror("Error getting file: ");
            closedir(d_ptr);
            return -1;
        }
    }

    closedir(d_ptr);
    return 0;
}



// #include <dirent.h>
// #include <errno.h>
// #include <limits.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <sys/limits.h>
// #include <sys/stat.h>
// #include <sys/types.h>

// #include "../file/fileListing.h"
// #include "../flags/flags.h"
// #include "../get/getFile.h"

// extern uint32_t app_flags;
// extern struct stat *statv;
// extern int statCount;

// int getDir(const char *path, struct fileListing **fl_arr, int *file_count) {

//     DIR *d_ptr;
//     struct dirent *dir_ptr;
//     int show_a = 0;
//     int entry_count = 0;
//     int rowcount = 0;
//     char *entries[255];

//     char file_path[PATH_MAX];
//     char *abs_path;

//     if ((d_ptr = opendir(path)) == NULL) {
//         fprintf(stderr, "Unable to open %s: %s\n", path, strerror(errno));
//         return -1;
//     }

//     while ((dir_ptr = readdir(d_ptr)) != NULL) {

//         if (!(app_flags & A_FLAG)) {

//             if ((strcmp(dir_ptr->d_name, ".") == 0 ||
//                  strcmp(dir_ptr->d_name, "..") == 0))
//                 continue;
//         }

//         if ((strcmp(dir_ptr->d_name, ".") != 0 &&
//              strcmp(dir_ptr->d_name, "..") != 0)) {
//             if (!(app_flags & a_FLAG)) {
//                 if (dir_ptr->d_name[0] == '.') {

//                     continue;
//                 }
//             }
//         }

//         snprintf(file_path, PATH_MAX, "%s/%s", path, dir_ptr->d_name);

//         if (getFile(file_path, fl_arr, file_count) != 0) {
//             perror("error getting file: ");
//             return -1;
//         }

//         //this seems like a bad ideas...
//         /*
//      * If the file is the directory entry or it's parent, rename the element just added to fileListing array
//      * to reflect it's relative name
//      */
//         if ((strcmp(dir_ptr->d_name, ".") == 0 ||
//              strcmp(dir_ptr->d_name, "..") == 0)){

//             (*fl_arr)[*file_count -1].name = dir_ptr->d_name;
//         }
//     }



//     (void)closedir(d_ptr);

//     return 0;
// }

// /*
//  * Fancy printing thingimajig
//  */
// // double result = (double)count / 5;
// // rowcount = (int)ceil(result);

// // for (int i = 0; i < count; i++) {
// //   for (int j = i + 1; j < count; j++) {
// //     if (strcmp(entries[i], entries[j]) > 0) {
// //       char *temp = entries[i];
// //       entries[i] = entries[j];
// //       entries[j] = temp;
// //     }
// //   }
// // }

// // for (int r = 0; r < rowcount; r++) {
// //   for (int c = 0; c < 5; c++) {
// //     int array_index = c * rowcount + r;

// //     if (array_index < count) {
// //       printf("%-16s\t", entries[array_index]);
// //     }
// //   }
// //   printf("\n");
// // }
