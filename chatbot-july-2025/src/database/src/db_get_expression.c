#include <database/data_base.h>
#include <error_handler.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct expression *db_get_expression(struct data_base *db,
                                     struct client *client, int type) {
  struct expressions *expr;
  int amount;
  int index;

  switch (type) {
  case FUNNY_JOKES_TYPE:
    expr = db->funny_jokes;
    amount = AMOUNT_OF_FUNNY_JOKES;
    break;

  case NOT_FUNNY_JOKES_TYPE:
    expr = db->not_funny_jokes;
    amount = AMOUNT_OF_NOT_FUNNY_JOKES;
    break;

  case SCIENTIFIC_QUOTES_TYPE:
    expr = db->quotes;
    amount = AMOUNT_OF_QUOTES;
    break;

  case LITERARY_QUOTES_TYPE:
    expr = db->l_quotes;
    amount = AMOUNT_OF_QUOTES;
    break;

  default:
    ERROR("incorrect type of expressions");
    return NULL;
    break;
  }

  srand(time(NULL));
  if (client == NULL) {
    index = rand() % amount;
    return &(expr->arr[index]);
  } else {
    index = rand() % expr->size;
    for (; index >= 0; index--) {
      if (expr->arr[index].owner == NULL) {
        return &(expr->arr[index]);
      } else if (strcmp(expr->arr[index].owner->username, client->username) ==
                 0) {
        return &(expr->arr[index]);
      }
    }
  }
  return NULL;
}