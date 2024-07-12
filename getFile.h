#ifndef GETFILE_H
#define GETFILE_H

#include "fileListing.h"
#include <sys/stat.h>

int getFile(const char *path, struct fileListing **fl_arr, int *file_count);

#endif // GETFILE_H
