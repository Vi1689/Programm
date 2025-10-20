#include <error_handler.h>
#include <stdio.h>

void error_handler(const char *file, const char *func, const int line,
                   char *msg) {
  fprintf(stderr, "[ОШИБКА][%s:%d] %s(): %s\n", file, line, func, msg);
}