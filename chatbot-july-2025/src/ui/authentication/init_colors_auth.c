#include <ui/ui_auth.h>

void init_colors_auth() {

  start_color();
  use_default_colors();
  init_pair(1, COLOR_WHITE, COLOR_BLUE);
  init_pair(2, COLOR_BLACK, COLOR_CYAN);
}