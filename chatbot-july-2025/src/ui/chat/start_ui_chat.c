#include <ui/ui_chat.h>

WINDOW *pad_chat;

int start_ui_chat(int client_fd, int num_of_messages) {

  initscr();
  noecho();
  cbreak();
  keypad(stdscr, TRUE);

  WINDOW *win_title = NULL;
  WINDOW *win_sidebar = NULL;
  WINDOW *win_input = NULL;
  pad_chat = NULL;
  if (init_colors_chat() < 0 ||
      create_windows(&win_title, &win_sidebar, &win_input, &pad_chat) < 0) {
    endwin();
    fprintf(stderr, "Initialization failed\n");
    return -1;
  }

  int res = run_chat_loop(win_input, client_fd, num_of_messages);

  delwin(win_input);
  delwin(pad_chat);
  delwin(win_sidebar);
  delwin(win_title);
  endwin();

  if (res == CHAT_BANNED) {
    printf(
        "Вы были заблокированы за многократное неверное написание команд!\n");
  } else if (res == CHAT_ERROR) {
    printf("Произошла некая ошибка, из-за которой завершилась работа чата\n");
  } else {
    printf("Работа чата завершилась успешно\n");
  }
  return 0;
}