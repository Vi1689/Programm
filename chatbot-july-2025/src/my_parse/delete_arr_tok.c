#include "my_parse/my_parse.h"

void delete_arr_tok(struct parse *tmp) {

  free(tmp->set_token);
  free(tmp);
}