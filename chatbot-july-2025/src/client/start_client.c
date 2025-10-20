#include <client/client.h>
#include <sodium.h>

char common_login[32];
struct client_message *credentials;

int start_client(int client_port, char *ip_address) {

  memset(common_login, 0, sizeof(common_login));
  int client_fd = create_sock(client_port, ip_address);
  if (client_fd == -1) {
    ERROR("client create_socket");
    endwin();
    return -1;
  }

  credentials = malloc(sizeof(struct client_message));
  if (start_ui_auth(credentials) == -1 || credentials == NULL) {
    ERROR("client start_ui_auth");
    delete_sock(client_fd);
    endwin();
    return -1;
  }
  strcpy(common_login, credentials->user_login);
  if (strlen(common_login) == 0) {
    ERROR("strcpy");
    delete_sock(client_fd);
    free(credentials);
    endwin();
    return -1;
  }

  if (sodium_init() == -1) {
    ERROR("sodium_init");
    delete_sock(client_fd);
    free(credentials);
    endwin();
    return -1;
  }

  char *result_auth = send_message_to_server(credentials->message, client_fd);
  if (result_auth == NULL) {
    ERROR("send_message_to_server");
    delete_sock(client_fd);
    free(credentials);
    endwin();
    return -1;
  }

  if (strstr(result_auth, "true") != NULL) {
    int num_of_messages = 0;
    sscanf(result_auth, "true %d", &num_of_messages);
    start_ui_chat(client_fd, num_of_messages);
  } else if (strcmp(result_auth, "false exist") == 0) {
    endwin();
    printf("Пользователь с таким логином уже существует\n");
  } else if (strcmp(result_auth, "error bd") == 0) {
    endwin();
    printf("Ошибка в базе данных\n");
  } else if (strcmp(result_auth, "misspel") == 0) {
    endwin();
    printf("\nВаш логин либо пароль содержит запрещенные символы: '~', '%%', "
           "''', '\"', ';', '.', ',', '/', '', ':'\n");
  } else if (strcmp(result_auth, "BAN") == 0) {
    endwin();
    printf(
        "Вы были заблокированы за многократное неверное написание команд!\n");
  } else {
    endwin();
    printf("Введен неверный логин либо пароль\n");
  }

  free(result_auth);
  free(credentials);
  delete_sock(client_fd);
  return 0;
}