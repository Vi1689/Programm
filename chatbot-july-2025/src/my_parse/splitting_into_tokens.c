#include "my_parse/my_parse.h"

int splitting_into_tokens(char *str, struct parse *a) {

  if (str == NULL || a == NULL) {
    return -1;
  }

  char word[256] = {'\000'};
  char old_word[256] = {'\000'};

  char *pch = strtok(str, " ");

  while (pch != NULL) {

    strcat(old_word, pch);
    size_t len = strlen(old_word);
    for (size_t i = 0; i < len; ++i) {
      word[i] = tolower(old_word[i]);
    }

    if (!strcmp(word, "\000")) {
      break;
    }

    struct token tmp = {0};
    strcpy(tmp.str, old_word);
    if (!strcmp(word, "/help")) {
      tmp.type = HELP;
      if (add_token(a, tmp) == -1) {
        return -1;
      }
    } else if (!strcmp(word, "/info")) {
      tmp.type = INFO;
      if (add_token(a, tmp) == -1) {
        return -1;
      }
    } else if (!strcmp(word, "/joke")) {
      tmp.type = JOKE;
      if (add_token(a, tmp) == -1) {
        return -1;
      }
    } else if (!strcmp(word, "/quote")) {
      tmp.type = QUOTE;
      if (add_token(a, tmp) == -1) {
        return -1;
      }
    } else if (!strcmp(word, "new")) {
      tmp.type = NEW;
      if (add_token(a, tmp) == -1) {
        return -1;
      }
    } else if (!strcmp(word, "/login")) {
      tmp.type = LOGIN;
      if (add_token(a, tmp) == -1) {
        return -1;
      }
    } else if (!strcmp(word, "/password")) {
      tmp.type = PASSWORD;
      if (add_token(a, tmp) == -1) {
        return -1;
      }
    } else if (!strcmp(word, "funny")) {
      tmp.type = FUNNY;
      if (add_token(a, tmp) == -1) {
        return -1;
      }
    } else if (!strcmp(word, "not_funny")) {
      tmp.type = NOT_FUNNY;
      if (add_token(a, tmp) == -1) {
        return -1;
      }
    } else if (!strcmp(word, "/chat")) {
      tmp.type = CHAT;
      if (add_token(a, tmp) == -1) {
        return -1;
      }
    } else if (!strcmp(word, "science")) {
      tmp.type = SCIENCE;
      if (add_token(a, tmp) == -1) {
        return -1;
      }
    } else if (!strcmp(word, "literary")) {
      tmp.type = LIT;
      if (add_token(a, tmp) == -1) {
        return -1;
      }
    } else if (!strcmp(word, "/update")) {
      tmp.type = UPDATA;
      if (add_token(a, tmp) == -1) {
        return -1;
      }
    } else {
      tmp.type = TEXT;
      if (add_token(a, tmp) == -1) {
        return -1;
      }
    }
    memset(word, '\000', sizeof(word));
    memset(old_word, '\000', sizeof(old_word));

    pch = strtok(NULL, " ");
  }

  struct token tmp = {0};
  tmp.type = END;
  if (add_token(a, tmp) == -1) {
    return -1;
  }

  return 0;
}