#include <ui/ui_chat.h>

void refresh_pad(int *pad_pos) {

  extern WINDOW *pad_chat;
  int max_y, max_x;
  getmaxyx(stdscr, max_y, max_x);
  int pos = (pad_pos != NULL) ? *pad_pos : 0;
  if (pos < 0) {
    pos = 0;
  }
  prefresh(pad_chat, pos, 0, 1, 0, max_y - INPUT_H - 1, max_x - SIDEBAR_W - 1);
}