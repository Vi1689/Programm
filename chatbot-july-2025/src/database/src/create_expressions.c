#include <database/expression.h>
#include <error_handler.h>
#include <malloc.h>

struct expressions *create_expressions(int size) {
  struct expressions *expr = malloc(sizeof(struct expressions));
  if (!expr) {
    ERROR("malloc fail");
    return NULL;
  }
  expr->capacity = size + 10;
  expr->size = 0;
  expr->arr = malloc(sizeof(struct expression) * expr->capacity);
  if (!expr->arr) {
    free(expr);
    ERROR("malloc fail");
    return NULL;
  }
  for (int i = 0; i < expr->capacity; i++) {
    expr->arr[i].expression = NULL;
  }
  return expr;
}