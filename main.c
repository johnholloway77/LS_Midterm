#include <stdio.h>

#include <stdint.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "./setFlags.h"
#include <stdlib.h>

#include "./checkFileType.h"
#include "./fileListing.h"
#include "./getDir.h"
#include "./getFile.h"
#include "./sortArray.h"
#include "./printListing.h"
#include "./dirQueue.h"

#ifdef DEBUG_MODE_ENABLED
#include "./checkFlags.h"
#include "./flags.h"
#endif

// initialize global flags variable
uint32_t app_flags = 0;

int main(int argc, char *argv[]) {

    Queue q;
    initQueue(&q);

  struct stat *statv = NULL;
  struct fileListing *fl_arr;
  fl_arr = malloc(sizeof(struct fileListing));

  int file_count = 0;

  int filetype = 0;

  /* This function will check if the effective user Id is 0 and
   * will set the A_FLAG if true
   */
  setEuidFlags(geteuid());

  if (argc == 1) {

      if(app_flags & d_FLAG){
          if (getFile(".", &fl_arr, &file_count) != 0) {
              perror("error getting file");
          }
      } else{
          getDir(".");
      }    // checkFlags(app_flags);
  } else if (argc > 1) {

    for (int i = 1; i < argc; i++) {

      if (argv[i][0] == '-') {
        setFlags(argv[i]);

        if (argc == 2) {
            if(app_flags & d_FLAG){
                if (getFile(".", &fl_arr, &file_count) != 0) {
                    perror("error getting file");
                }
            } else{
                  getDir(".");
            }
        }
        continue;
      }

      if ((filetype = checkFileType(argv[i])) == -1) {
        perror("Couldn't load file: ");
        char msg[275];
        snprintf(msg, sizeof(msg), "Could not load %s: ", argv[i]);
        perror(msg);
      }

      if (filetype == S_IFDIR) {
          if(app_flags & d_FLAG){
              if (getFile(argv[i], &fl_arr, &file_count) != 0) {
                  perror("error getting file");
              }
          } else{
              getDir(argv[i]);
          }
      }
      else if (filetype == S_IFREG) {
          if (getFile(argv[i], &fl_arr, &file_count) != 0) {
              perror("error getting file");
          }
      }
    }
  }

  sortArray(&fl_arr, file_count);

  printListing(fl_arr, file_count);

  free(fl_arr);
  return 0;
}
