#include "my_parse/my_parse.h"

int step_3(struct parse *a, size_t current_token, int old_tok, int tok,
           int *type, char *str) {

  if (a == NULL) {
    return -1;
  }

  struct token tmp = {0};

  switch (old_tok) {
  case NEW:
    if (tok == FUNNY) {
      next_token(&current_token);
      if (read_token(a, current_token, &tmp) == -1) {
        return -1;
      }
      if (tmp.type != END) {
        if (read_text(a, current_token, str) == -1) {

          return -1;
        }
        *type = PUSH_FUNNY;
      } else {
        *type = ERROR;
      }
    } else if (tok == NOT_FUNNY) {
      next_token(&current_token);
      if (read_token(a, current_token, &tmp) == -1) {
        return -1;
      }
      if (tmp.type != END) {
        if (read_text(a, current_token, str) == -1) {
          return -1;
        }
        *type = PUSH_NOT_FUNNY;
      } else {
        *type = ERROR;
      }

    } else if (tok == SCIENCE) {
      next_token(&current_token);
      if (read_token(a, current_token, &tmp) == -1) {
        return -1;
      }
      if (tmp.type != END) {
        if (read_text(a, current_token, str) == -1) {
          return -1;
        }
        *type = PUSH_SCIENCE;
      } else {
        *type = ERROR;
      }

    } else if (tok == LIT) {
      next_token(&current_token);
      if (read_token(a, current_token, &tmp) == -1) {
        return -1;
      }
      if (tmp.type != END) {
        if (read_text(a, current_token, str) == -1) {
          return -1;
        }
        *type = PUSH_LIT;
      } else {
        *type = ERROR;
      }

    } else {
      *type = ERROR;
    }
    break;

  case FUNNY:
    if (tok == END) {
      *type = FUNNY;
    } else {
      *type = ERROR;
    }
    break;

  case NOT_FUNNY:
    if (tok == END) {
      *type = NOT_FUNNY;
    } else {
      *type = ERROR;
    }
    break;

  case SCIENCE:
    if (tok == END) {
      *type = SCIENCE;
    } else {
      *type = ERROR;
    }
    break;

  case LIT:
    if (tok == END) {
      *type = LIT;
    } else {
      *type = ERROR;
    }
    break;

  default:
    *type = ERROR;
  }

  return 0;
}