#include <ui/ui_auth.h>
#include <ui/ui_chat.h>

char cur_screen[32] = {0};

int start_ui_auth() {

  initscr();
  init_colors_auth();
  cbreak();
  noecho();
  keypad(stdscr, TRUE);

  char login[FIELD_WIDTH + 1] = {0};
  char password[FIELD_WIDTH + 1] = {0};
  strcpy(cur_screen, "Authorization");
  if (create_auth_screen(cur_screen, login, password) == -1) {
    ERROR("create_auth_screen");
    endwin();
    return -1;
  }

  endwin();
  return 0;
}