#include <ui/ui_chat.h>

int init_colors_chat() {

  if (!has_colors()) {
    return -1;
  }

  start_color();
  use_default_colors();
  init_pair(1, COLOR_WHITE, COLOR_BLUE);
  init_pair(2, COLOR_WHITE, COLOR_CYAN);
  return 0;
}