#include <ui/ui_chat.h>

int draw_message_box(WINDOW *pad, int y, int x, const char *text,
                     bool from_bot) {
  extern char common_login[32];
  int width = getmaxx(pad);
  int max_box_w = width - 6;

  int text_len = strlen(text);
  int box_width = (text_len + 4 < MSG_WIDTH) ? text_len + 4 : MSG_WIDTH;
  if (box_width > max_box_w) {
    box_width = max_box_w;
  } else if (!from_bot && (size_t)box_width - 4 < strlen(common_login)) {
    box_width = strlen(common_login) + 4;
  }

  int box_height = 3;
  int line_length = 0;
  if (text_len + 4 > MSG_WIDTH) {
    for (int i = 0; text[i] != '\0'; ++i) {
      if (text[i] == '\n' || (text[i] == '$' && from_bot) ||
          ++line_length >= box_width - 4) {
        box_height++;
        line_length = 0;
      }
    }
  } else {
    for (int i = 0; text[i] != '\0'; ++i) {
      if (text[i] == '$' && from_bot) {
        box_height++;
        line_length = 0;
      }
    }
  }

  WINDOW *msg_win = derwin(pad, box_height, box_width, y, x);
  if (!msg_win) {
    return -1;
  }

  wbkgd(msg_win, COLOR_PAIR(1));
  box(msg_win, 0, 0);
  if (from_bot) {
    mvwprintw(msg_win, 0, 2, "Bot");
  } else {
    mvwprintw(msg_win, 0, 2, "%s", common_login);
  }

  int line_y = 1, line_x = 2;
  for (int i = 0; text[i] != '\0'; ++i) {
    if (line_y >= box_height - 1)
      break;

    if (text[i] == '\n' || (text[i] == '$' && from_bot)) {
      line_y++;
      line_x = 2;
    } else if (line_x >= box_width - 2) {
      line_y++;
      line_x = 2;
      if (line_y < box_height - 1) {
        mvwaddch(msg_win, line_y, line_x++, text[i]);
      }
    } else {
      mvwaddch(msg_win, line_y, line_x++, text[i]);
    }
  }

  wrefresh(msg_win);
  delwin(msg_win);
  return box_height;
}
