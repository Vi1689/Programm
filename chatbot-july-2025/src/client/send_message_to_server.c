#include <client/client.h>

char *send_message_to_server(char *message, int client_fd) {

  extern char common_login[32];
  if (message == NULL) {
    ERROR("client str is NULL");
    return NULL;
  }

  struct client_message send_message = {0};
  strcpy(send_message.user_login, common_login);
  memcpy(send_message.message, message, sizeof(send_message.message));

  struct sockaddr_in server = {0};
  server.sin_family = AF_INET;
  server.sin_port = htons(SERVER_PORT);
  if (inet_aton(SERVER_ADDRESS, &server.sin_addr) == 0) {
    ERROR("client inet_aton");
    return NULL;
  }

  if (my_send(client_fd, (char *)&send_message, sizeof(struct client_message),
              server) == -1) {
    ERROR("client my_send");
    return NULL;
  }

  char *answer = malloc(sizeof(struct client_message));
  if (answer == NULL) {
    ERROR("client malloc");
    return NULL;
  }

  ssize_t bytes_received =
      my_recv(client_fd, answer, sizeof(struct client_message), &server);
  if (bytes_received == -1) {
    ERROR("client recv");
    free(answer);
    return NULL;
  }

  size_t len = strlen(answer);
  if (len == 0) {
    return NULL;
  }

  while (len > 0 && (answer[len - 1] == '\n' || answer[len - 1] == '\r')) {
    answer[len - 1] = '\0';
    len--;
  }

  return answer;
}