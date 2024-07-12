#ifndef FILELISTING_H
#define FILELISTING_H

#include <sys/stat.h>

struct fileListing {
  struct stat st;
  char *name;
  char *path;
};

#endif // FILELISTING_H
