#include <ui/ui_auth.h>

WINDOW *create_window(int height, int width, int *win_h, int *win_w) {

  WINDOW *win = newwin(height, width, 2, 5);
  box(win, 0, 0);
  keypad(win, TRUE);
  getmaxyx(win, *win_h, *win_w);
  wbkgd(win, COLOR_PAIR(1));
  wattron(win, COLOR_PAIR(1));
  return win;
}