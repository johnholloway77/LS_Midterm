#ifndef STRFILENAME_H
#define STRFILENAME_H

#include <sys/stat.h>

char *strFileName(struct stat, char *name, char *path);

#endif // STRFILENAME_H
