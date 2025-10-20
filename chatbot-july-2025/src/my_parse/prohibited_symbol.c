#include "my_parse/my_parse.h"

int prohibited_symbol(const char *str) {

  size_t len = strlen(str);

  char forbidden[] = {'~', '%', '\'', '\"', ';', '.', ',', '/', '\\', ':'};

  for (size_t i = 0; i < len; ++i) {
    for (size_t j = 0; j < sizeof(forbidden) / sizeof(forbidden[0]); ++j) {
      if (str[i] == forbidden[j]) {
        return -1;
      }
    }
  }

  return 0;
}