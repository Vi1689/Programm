#include "my_analyzer/my_analyzer.h"
#include <sodium.h>

int analyzer(struct data_base *bd, struct client *client, char *in, char *str,
             size_t size_str, int *type) {

  if (in == NULL || bd == NULL || client == NULL || str == NULL ||
      size_str < 255) {
    return -1;
  }

  memset(str, '\000', size_str);

  if (db_is_client_banned(bd, client) == 1) {
    *type = BAN;
    return 0;
  }

  struct parse *root = create_arr_tok();
  if (root == NULL) {
    ERROR("create_arr_tok");
    return -1;
  }

  if (strstr(in, "/chat")) {
    if (db_push_message(bd, client, in + 6)) {
      ERROR("db_push_message");
      return -1;
    }
  }

  if (splitting_into_tokens(in, root) == -1) {
    delete_arr_tok(root);
    return -1;
  }

  if (step_1(root, type, str) == -1) {
    ERROR("step_1");
    return -1;
  }

  delete_arr_tok(root);

  return 0;
}
