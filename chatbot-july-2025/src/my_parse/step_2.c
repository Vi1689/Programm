#include "my_parse/my_parse.h"

int step_2(struct parse *a, size_t current_token, int old_tok, int tok,
           int *type, char *str) {

  if (a == NULL) {
    return -1;
  }

  struct token tmp = {0};

  switch (old_tok) {
  case JOKE:
    next_token(&current_token);
    if (read_token(a, current_token, &tmp) == -1) {
      return -1;
    }
    if (step_3(a, current_token, tok, tmp.type, type, str) == -1) {
      return -1;
    }
    break;

  case QUOTE:
    next_token(&current_token);
    if (read_token(a, current_token, &tmp) == -1) {
      return -1;
    }
    if (step_3(a, current_token, tok, tmp.type, type, str) == -1) {
      return -1;
    }
    break;

  case LOGIN:
    char login[256] = {'\000'};
    char password[256] = {'\000'};
    if (tok != END) {
      if (read_token(a, current_token, &tmp) == -1) {
        return -1;
      }
      strcpy(login, tmp.str);
      next_token(&current_token);
      if (read_token(a, current_token, &tmp) == -1) {
        return -1;
      }
      if (tmp.type == PASSWORD) {
        next_token(&current_token);
        if (read_token(a, current_token, &tmp) == -1) {
          return -1;
        }
        if (authorization(a, current_token, login, password, str, type) == -1) {
          return -1;
        }
      } else if (tmp.type != END) {
        strcpy(login, tmp.str);
        next_token(&current_token);
        if (read_token(a, current_token, &tmp) == -1) {
          return -1;
        }
        if (registration(a, current_token, login, password, str, type) == -1) {
          return -1;
        }
      } else {
        *type = ERROR;
      }
    } else {
      *type = ERROR;
    }
    break;

  default:
    *type = ERROR;
  }

  return 0;
}