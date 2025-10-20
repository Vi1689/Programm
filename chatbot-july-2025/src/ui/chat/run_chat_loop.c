#include <time.h>
#include <ui/ui_chat.h>

int pad_pos = 0;

int run_chat_loop(WINDOW *win_input, int client_fd, int num_of_messages) {
  ChatContext chat_context = {0};
  int sizeof_input = getmaxx(win_input) - 4;
  if (sizeof_input > 256) {
    sizeof_input = 256;
  }
  char input_buf[sizeof_input];
  int idx = 0;
  int ch;

  flushinp();
  wmove(win_input, 1, 3);
  wrefresh(win_input);

  if (print_history_of_messages(client_fd, num_of_messages, &chat_context) ==
      -1) {
    return CHAT_ERROR;
  }
  time_t last_update = time(NULL);
  while (true) {
    time_t current_time = time(NULL);
    if (current_time - last_update >= 10) {
      int count = 0;
      char buf[] = "/update";
      char *bot_response = send_message_to_server(buf, client_fd);
      if (strstr(bot_response, "yes")) {
        sscanf(bot_response, "yes %d", &count);
      }
      chat_context.msg_count = 0;
      memset(&chat_context.messages, 0, sizeof(Message) * MAX_MESSAGES);
      if (print_history_of_messages(client_fd, count, &chat_context) == -1) {
        return CHAT_ERROR;
      }
      last_update = current_time;
    }

    wrefresh(win_input);
    ch = wgetch(win_input);

    if (ch == KEY_F(1)) {
      return CHAT_SUCCESS;
    }

    if (ch == '\n') {
      input_buf[idx] = '\0';
      if (idx > 0) {
        add_message(input_buf, false, &chat_context);
        char buf[sizeof(input_buf) + 8];
        snprintf(buf, sizeof(buf), "/chat %s", input_buf);
        char *bot_response = send_message_to_server(buf, client_fd);
        if (strcmp(bot_response, "BAN") == 0) {
          free(bot_response);
          return CHAT_BANNED;
        }
        if (bot_response) {
          add_message(bot_response, true, &chat_context);
          free(bot_response);
        } else {
          add_message("Error: No response from server", true, &chat_context);
        }
      }
      idx = 0;
      werase(win_input);
      box(win_input, 0, 0);
      mvwprintw(win_input, 1, 1, "> ");
      wmove(win_input, 1, 3);
      wrefresh(win_input);

    } else if (ch == KEY_BACKSPACE || ch == 127) {
      if (idx > 0) {
        idx--;
        input_buf[idx] = '\0';
        int x = 3 + idx;
        mvwaddch(win_input, 1, x, ' ');
        wmove(win_input, 1, x);
        wrefresh(win_input);
      }
    } else if (ch == KEY_UP) {
      if (chat_context.pad_pos > 0) {
        chat_context.pad_pos--;
      }
      refresh_pad(&chat_context.pad_pos);

    } else if (ch == KEY_DOWN) {
      if (chat_context.pad_pos < chat_context.max_pos) {
        chat_context.pad_pos++;
        refresh_pad(&chat_context.pad_pos);
      }
    } else if (isprint(ch) && idx < (int)(sizeof(input_buf) - 1)) {
      input_buf[idx++] = ch;
      mvwaddch(win_input, 1, 3 + idx - 1, ch);
      wrefresh(win_input);
    }
  }
}