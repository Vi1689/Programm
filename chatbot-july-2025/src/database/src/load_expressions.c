#include <database/data_base.h>
#include <error_handler.h>
#include <malloc.h>
#include <stdio.h>
#include <string.h>

#define MAX_LINE_LEN 1024

int load_expressions(struct expressions *expr, int type) {
  FILE *fd;
  int amount;
  char buff[MAX_LINE_LEN];
  switch (type) {
  case FUNNY_JOKES_TYPE:
    fd = fopen("./expressions/funny_jokes", "r");
    if (fd == NULL) {
      ERROR("fopen fail");
      return 1;
    }
    amount = AMOUNT_OF_FUNNY_JOKES;
    break;

  case NOT_FUNNY_JOKES_TYPE:
    fd = fopen("./expressions/not_funny_jokes", "r");
    if (fd == NULL) {
      ERROR("fopen fail");
      return 1;
    }
    amount = AMOUNT_OF_NOT_FUNNY_JOKES;
    break;

  case SCIENTIFIC_QUOTES_TYPE:
    fd = fopen("./expressions/scientific_quotes", "r");
    if (fd == NULL) {
      ERROR("fopen fail");
      return 1;
    }
    amount = AMOUNT_OF_QUOTES;
    break;

  case LITERARY_QUOTES_TYPE:
    fd = fopen("./expressions/literary_quotes", "r");
    if (fd == NULL) {
      ERROR("fopen fail");
      return 1;
    }
    amount = AMOUNT_OF_QUOTES;
    break;

  default:
    ERROR("incorrect type of expressions");
    return 1;
    break;
  }
  for (int i = 0; i < amount; i++) {
    if (fgets(&(buff[0]), MAX_LINE_LEN, fd) == NULL) {
      ERROR("fgets fail");
      return 1;
    }
    int len = strlen(&(buff[0])) + 1;
    expr->arr[i].owner = NULL;
    expr->arr[i].len = len;
    expr->arr[i].expression = malloc(sizeof(char) * len);
    if (expr->arr[i].expression == NULL) {
      ERROR("malloc fail");
      return 1;
    }
    strcpy(expr->arr[i].expression, &(buff[0]));
    expr->size++;
  }
  fclose(fd);
  return 0;
}