#include <ctype.h>
#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#include "../flags/flags.h"
#define BUFFER_SIZE 256

extern uint32_t app_flags;

char *strFileName(struct stat stat, const char *name, const char *path) {
    char *buffer = (char *)malloc(BUFFER_SIZE);
    if (buffer == NULL) {
        perror("failed to allocate memory for buffer");
        return NULL;
    }

    memset(buffer, 0, BUFFER_SIZE);
    int i = 0;

    const char *path_name = strrchr(path, '/');
    if (path_name != NULL) {
        path_name++;
    } else {
        path_name = path;
    }

    if (strcmp("..", path_name) != 0 && strcmp(".", path_name) != 0) {
        if (app_flags & w_FLAG) {
            while (*name && i < BUFFER_SIZE - 1) {
                buffer[i++] = (unsigned char)*name++;
            }
        } else if (app_flags & q_FLAG) {
            while (*name && i < BUFFER_SIZE - 1) {
                buffer[i++] = isprint((unsigned char)*name) ? (unsigned char)*name : '?';
                name++;
            }
        } else {
            while (*name && i < BUFFER_SIZE - 3) {
                if (isprint((unsigned char)*name)) {
                    buffer[i++] = (unsigned char)*name;
                } else {
                    snprintf(buffer + i, BUFFER_SIZE - i, "%02x", (unsigned char)*name);
                    i += 2;
                }
                name++;
            }
        }
    } else {
        strlcpy(buffer, strcmp(".", path_name) == 0 ? "." : "..", BUFFER_SIZE);
        i += strcmp(".", path_name) == 0 ? 1 : 2;
    }

    if (app_flags & F_FLAG) {
        if (S_ISDIR(stat.st_mode)) {
            i += snprintf(buffer + i, BUFFER_SIZE - i, "/");
        } else if (S_ISLNK(stat.st_mode)) {
            i += snprintf(buffer + i, BUFFER_SIZE - i, "@");
        } else if (S_ISWHT(stat.st_mode)) {
            i += snprintf(buffer + i, BUFFER_SIZE - i, "%%");
        } else if (S_ISSOCK(stat.st_mode)) {
            i += snprintf(buffer + i, BUFFER_SIZE - i, "=");
        } else if (S_ISFIFO(stat.st_mode)) {
            i += snprintf(buffer + i, BUFFER_SIZE - i, "|");
        } else if (S_ISREG(stat.st_mode)) {
            if (stat.st_mode & (S_ISTXT | S_IXUSR | S_IXGRP | S_IXOTH)) {
                i += snprintf(buffer + i, BUFFER_SIZE - i, "*");
            }
        }
    }

    if (S_ISLNK(stat.st_mode)) {
        char destination[BUFFER_SIZE];
        memset(destination, 0, BUFFER_SIZE);
        ssize_t len = readlinkat(AT_FDCWD, path, destination, sizeof(destination) - 1);
        if (len != -1) {
            snprintf(buffer + i, BUFFER_SIZE - i, " --> %s", destination);
        } else {
            perror("readlinkat");
        }
    }

    return buffer;
}
