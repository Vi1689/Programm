#include "my_analyzer/my_analyzer.h"
#include "my_network/my_network.h"

int send_history_mess(int fd, struct sockaddr_in sock, struct data_base *bd,
                      struct client *client) {

  struct message *tmp = db_get_messages(bd, client);

  while (tmp != NULL) {
    if (my_send(fd, tmp->text, strlen(tmp->text), sock) == -1) {
      return -1;
    }
    tmp = tmp->next;
  }
  return 0;
}