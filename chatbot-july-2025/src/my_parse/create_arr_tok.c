#include "my_parse/my_parse.h"

struct parse *create_arr_tok() {

  struct parse *tmp = malloc(sizeof(struct parse));

  if (tmp == NULL) {
    return NULL;
  }

  tmp->size = 0;
  tmp->set_token = NULL;

  return tmp;
}