#include <stdio.h>

#include <stdint.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "flags/setFlags.h"
#include <stdlib.h>

#include "file/checkFileType.h"
#include "file/fileListing.h"
#include "get/getDir.h"
#include "get/getFile.h"
#include "print/printListing.h"
#include "queue/dirQueue.h"
#include "sort/sortArray.h"
#include "get/recurDir.h"

#ifdef DEBUG_MODE_ENABLED
#include "flags/checkFlags.h"
#include "flags/flags.h"
#endif

// initialize global flags variable
uint32_t app_flags = 0;

int main(int argc, char *argv[]) {

  Queue q;
  initQueue(&q);
  char *path;

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

    if (app_flags & d_FLAG) {
      if (getFile(".", &fl_arr, &file_count) != 0) {
        perror("error getting file");
      }
    } else {
      //getDir(".");
        enqueue(&q, ".");
    }
  } else if (argc > 1) {

    for (int i = 1; i < argc; i++) {

      if (argv[i][0] == '-') {
        setFlags(argv[i]);

        if (argc == 2) {
          if (app_flags & d_FLAG) {
            if (getFile(".", &fl_arr, &file_count) != 0) {
              perror("error getting file");
            }
          } else {
            enqueue(&q, ".");
            //getDir(".");
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
        if (app_flags & d_FLAG) {
          if (getFile(argv[i], &fl_arr, &file_count) != 0) {
            perror("error getting file");
          }
        } else {
          //getDir(argv[i]);
            enqueue(&q, argv[i]);
        }
      } else if (filetype == S_IFREG) {
        if (getFile(argv[i], &fl_arr, &file_count) != 0) {
          perror("error getting file");
        }
      }
      else if(filetype == S_IFLNK){
          if(getFile(argv[i], &fl_arr, &file_count) != 0){
              perror("error getting symlink file: ");
          }
      }



    }
  }

  sortArray(&fl_arr, file_count);

  printListing(fl_arr, file_count);

  free(fl_arr);



  while ((path = dequeue(&q)) != NULL){


      if(app_flags & R_FLAG){
          recurDir(path);
      } else{
          struct fileListing *queue_fl_arr = malloc(sizeof(struct fileListing));
          int queue_file_count = 0;

          getDir(path, &queue_fl_arr, &queue_file_count);

          sortArray(&queue_fl_arr, queue_file_count);
          printListing(queue_fl_arr, queue_file_count);
          free(path);
          free(queue_fl_arr);
      }

  }

    return 0;
}
