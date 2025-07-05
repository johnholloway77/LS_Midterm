#ifndef SETFLAGS_H
#define SETFLAGS_H

/*
 * This flag should be able to be read from any function,
 * but unable to be edited after being changed.
 */
extern const uint32_t app_flags;

int setFlags(const char *flag_str);
int setEuidFlags(int euid);

#endif // SETFLAGS_H
