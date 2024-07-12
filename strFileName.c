#include <ctype.h>
#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#include "./flags.h"
#define BUFFER_SIZE 256

extern uint32_t app_flags;

char *strFileName(struct stat stat, char *name, char *path) {

  char *buffer = (char *)malloc(BUFFER_SIZE);
  int i = 0;

  if (buffer == NULL) {
    perror("failed t allocate memmory for buffer ");
    return NULL;
  }

  memset_s(buffer, BUFFER_SIZE, 0, BUFFER_SIZE);

  if (app_flags & w_FLAG) {
    while (*name) {
      buffer[i] = (unsigned char)*name;
      i++;
    }

    // return buffer;

  } else if (app_flags & q_FLAG) {

    while (*name) {

      if (isprint((unsigned char)*name) == 0) {

        buffer[i] = '?';
        i++;
      }
      buffer[i] = (unsigned char)*name;
      i++;
      name++;
    }

    // return buffer;
  } else {

    while (*name) {
      if (isprint((unsigned char)*name)) {
        buffer[i] = (unsigned char)*name;
        i++;
      } else {
        snprintf(buffer + i, BUFFER_SIZE - i, "%02x", (unsigned char)*name);
        i += 2;
      }

      name++;
    }

    // return buffer;
  }

  if (app_flags & F_FLAG) {

    if (S_ISDIR(stat.st_mode)) {
      i += snprintf(buffer + i, BUFFER_SIZE - i, "/");
    } else if (S_ISLNK(stat.st_mode)) {
      i += snprintf(buffer + i, BUFFER_SIZE - i, "@");
    } else if (S_ISWHT(stat.st_mode)){
        i += snprintf(buffer + i, BUFFER_SIZE - i, "%%");
    } else if(S_ISSOCK(stat.st_mode)){
        i += snprintf(buffer + i, BUFFER_SIZE - i, "=");
    } else if(S_ISFIFO(stat.st_mode)){
        i += snprintf(buffer + i, BUFFER_SIZE - i, "|");
    } else if(S_ISREG(stat.st_mode)){
        if(stat.st_mode & S_ISTXT || stat.st_mode & S_IXUSR || stat.st_mode & S_IXGRP || stat.st_mode & S_IXOTH){
            i += snprintf(buffer + i, BUFFER_SIZE - i, "*");
        }
    }
  }

  if (S_ISLNK(stat.st_mode)){

      char destination[BUFFER_SIZE];
      memset_s(destination, BUFFER_SIZE, 0, BUFFER_SIZE);
      size_t len;

      len = readlinkat(AT_FDCWD, path, destination, sizeof(destination));
      if (len == -1) {
          perror("readlinkat");
          //return NULL;
      }


     // printf(" --> %s\n", destination);
      snprintf(buffer + i, BUFFER_SIZE - i, " --> %s", destination);
  }

  return buffer;
}
