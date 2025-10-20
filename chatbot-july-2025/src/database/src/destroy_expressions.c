#include <database/expression.h>
#include <malloc.h>

void destroy_expressions(struct expressions *expr) {
  for (int i = 0; i < expr->capacity; i++) {
    if (expr->arr[i].expression) {
      free(expr->arr[i].expression);
    }
  }
  free(expr->arr);
  free(expr);
}
