#include <ui/ui_chat.h>

int create_windows(WINDOW **win_title, WINDOW **win_sidebar, WINDOW **win_input,
                   WINDOW **pad_chat) {

  int max_y, max_x;
  getmaxyx(stdscr, max_y, max_x);

  *win_title = newwin(1, max_x, 0, 0);
  if (!*win_title) {
    return -1;
  }

  wbkgd(*win_title, COLOR_PAIR(1));
  mvwprintw(*win_title, 0, (max_x - strlen(TITLE)) / 2, "%s", TITLE);
  wrefresh(*win_title);

  *win_sidebar = newwin(max_y - INPUT_H - 1, SIDEBAR_W, 1, max_x - SIDEBAR_W);

  if (!*win_sidebar) {
    return -1;
  }

  wbkgd(*win_sidebar, COLOR_PAIR(1));
  box(*win_sidebar, 0, 0);

  mvwprintw(*win_sidebar, 8, 5, "Commands");
  mvwprintw(*win_sidebar, 11, 6, "/help");
  mvwprintw(*win_sidebar, 12, 6, "/info");
  mvwprintw(*win_sidebar, 13, 6, "/joke");
  mvwprintw(*win_sidebar, 14, 6, "/quote");
  mvwprintw(*win_sidebar, max_y - INPUT_H - 3, 4, "F1 to exit");

  wrefresh(*win_sidebar);

  int chat_w = max_x - SIDEBAR_W;
  *pad_chat = newpad(1000, chat_w);

  if (!*pad_chat) {
    return -1;
  }

  wbkgd(*pad_chat, COLOR_PAIR(2));
  scrollok(*pad_chat, TRUE);
  werase(*pad_chat);
  refresh_pad(NULL);

  *win_input = newwin(INPUT_H, max_x, max_y - INPUT_H, 0);

  if (!*win_input) {
    return -1;
  }

  wbkgd(*win_input, COLOR_PAIR(1));
  box(*win_input, 0, 0);
  mvwprintw(*win_input, 1, 1, "> ");
  wrefresh(*win_input);
  keypad(*win_input, TRUE);

  return 0;
}