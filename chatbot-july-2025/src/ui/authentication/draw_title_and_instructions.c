#include <ui/ui_auth.h>

void draw_title_and_instructions(WINDOW *win, const char *title, int win_h,
                                 int win_w) {

  int mid_y = win_h / 2;
  mvwprintw(win, mid_y - 3, (win_w - strlen(title)) / 2, "%s", title);

  if (strcmp(title, "Registration") == 0) {
    mvwprintw(win, win_h - 3, 2, "F1=Submit  F2=Authorization  F3=Quit");
  } else {
    mvwprintw(win, win_h - 3, 2, "F1=Submit  F2=Register  F3=Quit");
  }
  wrefresh(win);
}