#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../flags/flags.h"
#define MAX_DIGITS 25

extern uint32_t app_flags;

char *strFileSize(off_t st_size) {

  char *str = (char *)malloc(sizeof(char) * MAX_DIGITS + 1);

  memset(str, 0, MAX_DIGITS + 1);

  if (app_flags & h_FLAG) {
    double dbl_size = st_size * 1.0;
    int i = 0;
    char suffix[5] = {'B', 'K', 'M', 'G', 'T'};

    while (dbl_size >= 1024.0) {
      i++;
      dbl_size = dbl_size / 1024.0;
    }

    snprintf(str, MAX_DIGITS + 1, "%1.1f%c", dbl_size, suffix[i]);
    return str;
  }
  if (app_flags & k_FLAG) {
    snprintf(str, MAX_DIGITS + 1, "%1.3f", st_size / 1024.0);
    return str;
  } else {
    snprintf(str, MAX_DIGITS + 1, "%ld", st_size);
    return str;
  }
}
