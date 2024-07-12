#ifndef GETDIR_H
#define GETDIR_H
#include "./fileListing.h"

int getDir(const char *path, struct fileListing **fl_arr, int *file_count);

#endif // GETDIR_H
