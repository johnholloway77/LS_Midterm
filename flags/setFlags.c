#include "flags.h"
#include <stdint.h>
#include <string.h>

extern uint32_t app_flags;
int setFlags(const char *flag_str) {
  int length = strlen(flag_str);

  for (int i = 1; i < length; i++) {

    if (flag_str[i] == 'A') {
      app_flags = app_flags | A_FLAG;
    }

    if (flag_str[i] == 'a') {
      app_flags = app_flags | a_FLAG;
    }
    if (flag_str[i] == 'c') {
      if (app_flags & u_FLAG) {
        app_flags = app_flags & ~u_FLAG;
      }

      app_flags = app_flags | c_FLAG;
    }
    if (flag_str[i] == 'd') {
      app_flags = app_flags | d_FLAG;
    }
    if (flag_str[i] == 'F') {
      app_flags = app_flags | F_FLAG;
    }
    if (flag_str[i] == 'f') {
      app_flags = app_flags | f_FLAG;
    }
    if (flag_str[i] == 'h') {
      app_flags = app_flags | h_FLAG;
    }
    if (flag_str[i] == 'i') {
      app_flags = app_flags | i_FLAG;
    }
    if (flag_str[i] == 'k') {
      app_flags = app_flags | k_FLAG;
    }
    if (flag_str[i] == 'l') {
      if (app_flags & n_FLAG) {
        app_flags = app_flags & ~n_FLAG;
      }

      app_flags = app_flags | l_FLAG;
    }
    if (flag_str[i] == 'n') {
      if (app_flags & l_FLAG) {
        app_flags = app_flags & ~l_FLAG;
      }
      app_flags = app_flags | n_FLAG;
    }

    if (flag_str[i] == 'o') {
      app_flags = app_flags | o_FLAG;
    }

    if (flag_str[i] == 'q') {

      if (app_flags & w_FLAG) {
        app_flags = app_flags & ~w_FLAG;
      }

      app_flags = app_flags | q_FLAG;
    }
    if (flag_str[i] == 'R') {
      app_flags = app_flags | R_FLAG;
    }
    if (flag_str[i] == 'r') {
      app_flags = app_flags | r_FLAG;
    }
    if (flag_str[i] == 'S') {
      app_flags = app_flags | S_FLAG;
    }
    if (flag_str[i] == 's') {
      app_flags = app_flags | s_FLAG;
    }
    if (flag_str[i] == 't') {
      app_flags = app_flags | t_FLAG;
    }
    if (flag_str[i] == 'u') {
      if (app_flags & c_FLAG) {
        app_flags = app_flags & ~c_FLAG;
      }
      app_flags = app_flags | u_FLAG;
    }
    if (flag_str[i] == 'w') {

      if (app_flags & q_FLAG) {
        app_flags = app_flags & ~q_FLAG;
      }

      app_flags = app_flags | w_FLAG;
    }
  }

  return 0;
}

int setEuidFlags(int euid) {
  if (euid == 0) {
    app_flags = app_flags | A_FLAG;
  }

  return 0;
}
