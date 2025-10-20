#include <ui/ui_auth.h>

void draw_labels(WINDOW *win, int login_y, int pass_y, int start_x) {

  mvwprintw(win, login_y + 1, start_x - 1, "   Login ");
  mvwprintw(win, pass_y + 1, start_x - 1, "Password ");
}