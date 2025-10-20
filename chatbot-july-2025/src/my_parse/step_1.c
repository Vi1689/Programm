#include "my_parse/my_parse.h"

int step_1(struct parse *a, int *type, char *str) {

  if (a == NULL) {
    return -1;
  }

  size_t current_token = 0;

  struct token tmp = {0};
  if (read_token(a, current_token, &tmp) == -1) {
    return -1;
  }

  if (tmp.type == CHAT) {
    next_token(&current_token);
    if (read_token(a, current_token, &tmp) == -1) {
      return -1;
    }
    switch (tmp.type) {
    case HELP:
      next_token(&current_token);
      if (read_token(a, current_token, &tmp) == -1) {
        return -1;
      }
      if (tmp.type == END) {
        *type = HELP;
      } else {
        *type = ERROR;
      }
      break;

    case INFO:
      next_token(&current_token);
      if (read_token(a, current_token, &tmp) == -1) {
        return -1;
      }
      if (tmp.type == END) {
        *type = INFO;
      } else {
        *type = ERROR;
      }
      break;

    case JOKE:
      next_token(&current_token);
      if (read_token(a, current_token, &tmp) == -1) {
        return -1;
      }
      if (tmp.type == END) {
        *type = JOKE;
      } else {
        if (step_2(a, current_token, JOKE, tmp.type, type, str) == -1) {
          *type = ERROR;
        }
      }
      break;

    case QUOTE:
      next_token(&current_token);
      if (read_token(a, current_token, &tmp) == -1) {
        return -1;
      }
      if (tmp.type == END) {
        *type = QUOTE;
      } else {
        if (step_2(a, current_token, QUOTE, tmp.type, type, str) == -1) {
          *type = ERROR;
        }
      }
      break;

    default:
      *type = ERROR;
    }
  } else if (tmp.type == LOGIN) {
    next_token(&current_token);
    if (read_token(a, current_token, &tmp) == -1) {
      return -1;
    }
    if (step_2(a, current_token, LOGIN, tmp.type, type, str) == -1) {
      *type = ERROR;
    }
  } else if (tmp.type == UPDATA) {
    *type = UPDATA;
  } else {
    *type = ERROR;
  }

  return 0;
}