#include <stdlib.h>

#include <dirent.h>

#include <grp.h>
#include <libgen.h>
#include <pwd.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/syslimits.h>
#include <sys/types.h>
#include <time.h>

#include "../file/fileListing.h"


extern uint32_t app_flags;
int getFile(const char *path, struct fileListing **fl_arr, int *file_count) {
  struct stat st;
  char *file_mode;
  char path_str[PATH_MAX];
  char *abs_path;
  abs_path = realpath(path, NULL);

  if (lstat(path, &st) != 0) {
    perror("Could't get file stat: ");
    return -1;
  }



 // if(S_ISDIR(st.st_mode) && app_flags & R_FLAG){
 //     //getDir(path, fl_arr, file_count);
 //     printf("dir file!\n");
 // }
 //   else{
    (*file_count)++;
  struct fileListing *tmp_ptr;
  tmp_ptr = realloc(*fl_arr, sizeof(struct fileListing) * (*file_count));
  if (tmp_ptr == NULL) {
    perror("Unable to reallocate memory for *tmp_ptr");
    return -1;
  }

  *fl_arr = tmp_ptr;
  strlcpy(path_str, path, sizeof(path_str));

  char *tempName;

  if((tempName  = strrchr(path, '/')) != NULL){
      tempName++;
      (*fl_arr)[*file_count - 1].name = strdup(tempName);
  }else{
    (*fl_arr)[*file_count - 1].name = strdup(path);
  }
  //(*fl_arr)[*file_count - 1].name = strdup(basename(abs_path));

  (*fl_arr)[*file_count - 1].st = st;
  if (S_ISLNK(st.st_mode)) {
    int pathLength = strlen(path) + 1;
    char *path_ptr = (char *)malloc(pathLength);
    strlcpy(path_ptr, path, pathLength);
    (*fl_arr)[*file_count - 1].path = path_ptr;

  } else {
    (*fl_arr)[*file_count - 1].path = strdup(path);
  }

  free(abs_path);

  //}

  return 0;
}
