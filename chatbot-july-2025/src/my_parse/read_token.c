#include "my_parse/my_parse.h"

int read_token(struct parse *a, size_t current_token, struct token *tmp) {

  if (current_token >= a->size || a == NULL) {
    return -1;
  }

  *tmp = a->set_token[current_token];

  return 0;
}
