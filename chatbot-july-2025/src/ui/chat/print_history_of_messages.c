#include <ui/ui_chat.h>

int print_history_of_messages(int client_fd, int num_of_messages,
                              ChatContext *chat_context) {

  if (num_of_messages == 0) {
    return 0;
  }
  char *message = malloc(sizeof(char) * 512);
  if (message == NULL) {
    ERROR("print_history_of_messages malloc");
    return -1;
  }
  struct sockaddr_in server = {0};

  for (int i = 0; i < num_of_messages; i++) {
    if (my_recv(client_fd, message, 512, &server) == -1) {
      free(message);
      return -1;
    }
    size_t len = strlen(message);
    if (len == 0) {
      free(message);
      return -1;
    }

    while (len > 0 && (message[len - 1] == '\n' || message[len - 1] == '\r')) {
      message[len - 1] = '\0';
      len--;
    }

    if (add_message(message, i & 1, chat_context) == -1) {
      ERROR("print_history_of_messages add_message");
      break;
    }
    memset(message, 0, 512);
  }
  free(message);
  return 0;
}