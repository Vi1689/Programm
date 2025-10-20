#include "my_parse/my_parse.h"

int add_token(struct parse *a, struct token tok) {

  void *tmp = realloc(a->set_token, (a->size + 1) * sizeof(struct token));

  if (tmp == NULL) {
    ERROR("realloc");
    return -1;
  }

  a->set_token = tmp;

  a->set_token[a->size] = tok;

  a->size++;

  return 0;
}