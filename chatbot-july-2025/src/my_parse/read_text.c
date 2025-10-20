#include "my_parse/my_parse.h"

int read_text(struct parse *a, size_t current_token, char *str) {

  if (a == NULL || str == NULL) {
    return -1;
  }

  struct token tmp = {0};
  if (read_token(a, current_token, &tmp) == -1) {
    return -1;
  }
  while (tmp.type != END) {
    strcat(str, tmp.str);
    strcat(str, " ");
    next_token(&current_token);
    if (read_token(a, current_token, &tmp) == -1) {
      return -1;
    }
  }
  str[strlen(str) - 1] = '\000';
  return 0;
}