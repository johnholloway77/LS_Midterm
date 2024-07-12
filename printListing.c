#include <grp.h>
#include <math.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include "./fileListing.h"
#include "./flags.h"
#include "./strFileMode.h"
#include "./strFileName.h"
#include "./strFileSize.h"
#include "./strFileTime.h"

#define MAX_BUFFER_SIZE 255

extern uint32_t app_flags;

int printListing(struct fileListing *fl_arr, int file_count) {

  for (int i = 0; i < file_count; i++) {

    char *name_str;
    char *mode_str;
    char *time_str;
    char *size_str;
    char str_buf[MAX_BUFFER_SIZE];
    int buf_pos = 0;

    // initialize buffer with null chars

    memset(str_buf, 0, MAX_BUFFER_SIZE);

    // check for inode flag and add it to string if called.
    if (app_flags & i_FLAG) {
      buf_pos += snprintf(str_buf + buf_pos, MAX_BUFFER_SIZE - buf_pos, "%ld ",
                          fl_arr[i].st.st_ino);
    }

    if (app_flags & s_FLAG) {

      char *blocksize = getenv("BLOCKSIZE");
      if (blocksize != NULL) {
        double blk_size = atof(blocksize);
        double blocks = ceil(fl_arr[i].st.st_blksize / blk_size);
        buf_pos += snprintf(str_buf + buf_pos, MAX_BUFFER_SIZE - buf_pos, "%d ",
                            (int)blocks);
      } else {
        buf_pos += snprintf(str_buf + buf_pos, MAX_BUFFER_SIZE - buf_pos,
                            "%ld ", fl_arr[i].st.st_blocks);
      }

      // printf("blocksize: %d blocks: %ld ", fl_arr[i].st.st_blksize,
      // fl_arr[i].st.st_blocks);
    }

    if (app_flags & l_FLAG || app_flags & n_FLAG) {

      mode_str = strFileMode(fl_arr[i].st);
      if (mode_str == NULL) {
        perror("Couldn't allocate memory for mode string: ");
        return -1;
      }

      size_str = strFileSize(fl_arr[i].st.st_size);
      if (size_str == NULL) {
        perror("Couldn't allocate memory for size string: ");
        return -1;
      }

      time_str = strFileTime(fl_arr[i].st);
      if (time_str == NULL) {
        perror("Couldn't allocate memory for time string: ");
        return -1;
      }

      if (app_flags & l_FLAG) {

        char *userName = getpwuid(fl_arr[i].st.st_uid)->pw_name;
        char *groupName = getgrgid(fl_arr[i].st.st_gid)->gr_name;

        if (app_flags & o_FLAG) {

          char *arch = fl_arr[i].st.st_flags & UF_ARCHIVE ? "uarch" : "-";
          buf_pos += snprintf(str_buf + buf_pos, MAX_BUFFER_SIZE - buf_pos,
                              "%s %ld %s %s %s %s %s ", mode_str,
                              fl_arr[i].st.st_nlink, userName, groupName, arch,
                              size_str, time_str);
        } else {
          buf_pos +=
              snprintf(str_buf + buf_pos, MAX_BUFFER_SIZE - buf_pos,
                       "%s %ld %s %s %s %s ", mode_str, fl_arr[i].st.st_nlink,
                       userName, groupName, size_str, time_str);
        }

        free(userName);
        free(groupName);

      } else if (app_flags & n_FLAG) {

        if (app_flags & o_FLAG) {
          char *arch = fl_arr[i].st.st_flags & UF_ARCHIVE ? "uarch" : "-";
          buf_pos += snprintf(
              str_buf + buf_pos, MAX_BUFFER_SIZE - buf_pos,
              "%s %ld %u %u %s %s %s ", mode_str, fl_arr[i].st.st_nlink,
              fl_arr[i].st.st_uid, fl_arr[i].st.st_gid, arch,
              strFileSize(fl_arr[i].st.st_size), strFileTime(fl_arr[i].st));
        } else {

          buf_pos += snprintf(
              str_buf + buf_pos, MAX_BUFFER_SIZE - buf_pos,
              "%s %ld %u %u %s %s ", mode_str, fl_arr[i].st.st_nlink,
              fl_arr[i].st.st_uid, fl_arr[i].st.st_gid,
              strFileSize(fl_arr[i].st.st_size), strFileTime(fl_arr[i].st));
        }
      }

      free(mode_str);
      free(size_str);
      free(time_str);
    }

    name_str = strFileName(fl_arr[i].st, fl_arr[i].name, fl_arr[i].path);
    if (name_str == NULL) {
      perror("couldn't allocate memory for name: ");
      return -1;
    }

    buf_pos +=
        snprintf(str_buf + buf_pos, MAX_BUFFER_SIZE - buf_pos, "%s", name_str);
    free(name_str);

    free(fl_arr[i].name);
    if (S_ISLNK(fl_arr[i].st.st_mode)) {
      free(fl_arr[i].path);
    }

    printf("%s\n", str_buf);
  }

  return 0;
}

/*
 * Fancy printing thingimajig
 * If I were really fancy I'd find out the column width and base the output on
 * that
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
