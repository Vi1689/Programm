#include "my_parse/my_parse.h"

int registration(struct parse *a, size_t current_token, char *login,
                 char *password, char *str, int *type) {

  if (a == NULL || login == NULL || password == NULL || str == NULL) {
    return -1;
  }

  struct token tmp = {0};

  if (read_token(a, current_token, &tmp) == -1) {
    return -1;
  }

  if (tmp.type == PASSWORD) {
    next_token(&current_token);
    if (read_token(a, current_token, &tmp) == -1) {
      return -1;
    }
    if (tmp.type == NEW) {
      next_token(&current_token);
      if (read_token(a, current_token, &tmp) == -1) {
        return -1;
      }
      if (tmp.type != END) {
        strcpy(password, tmp.str);
        next_token(&current_token);
        if (read_token(a, current_token, &tmp) == -1) {
          return -1;
        }
        if (tmp.type == END) {
          *type = REGISTR;
          strcat(str, login);
          strcat(str, " ");
          strcat(str, password);
          if (prohibited_symbol(str) == -1) {
            *type = MISSPELL;
          }
        } else {
          *type = MISSPELL;
        }
      } else {
        *type = MISSPELL;
      }
    } else {
      *type = MISSPELL;
    }
  } else {
    *type = MISSPELL;
  }

  return 0;
}