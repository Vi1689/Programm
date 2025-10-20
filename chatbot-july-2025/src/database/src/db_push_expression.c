#include <database/data_base.h>
#include <error_handler.h>
#include <malloc.h>
#include <string.h>

int db_push_expression(struct data_base *db, struct expression *expr,
                       int type) {
  struct expressions *exprs;

  switch (type) {
  case FUNNY_JOKES_TYPE:
    exprs = db->funny_jokes;
    break;

  case NOT_FUNNY_JOKES_TYPE:
    exprs = db->not_funny_jokes;
    break;

  case SCIENTIFIC_QUOTES_TYPE:
    exprs = db->quotes;
    break;

  case LITERARY_QUOTES_TYPE:
    exprs = db->l_quotes;
    break;

  default:
    ERROR("incorrect type of expressions");
    return 1;
    break;
  }

  if (exprs->size == exprs->capacity) {
    exprs->arr = realloc(exprs->arr, exprs->capacity * 2);
    if (!exprs->arr) {
      ERROR("realloc fail");
      return 1;
    }
    exprs->capacity *= 2;
    for (int i = exprs->size; i < exprs->capacity; i++) {
      exprs->arr[i].expression = NULL;
    }
  }
  exprs->arr[exprs->size].len = expr->len;
  exprs->arr[exprs->size].owner = expr->owner;
  exprs->arr[exprs->size].expression = malloc(sizeof(char) * expr->len);
  if (!exprs->arr[exprs->size].expression) {
    ERROR("malloc fail");
    return 1;
  }
  strcpy(exprs->arr[exprs->size].expression, expr->expression);
  exprs->size++;
  return 0;
}
