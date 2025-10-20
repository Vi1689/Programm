#include <database/hashtable/hash_table.h>
#include <database/message.h>
#include <malloc.h>

void destroy_chain(struct node *node) {
  if (node->next != NULL) {
    destroy_chain(node->next);
  }

  if (node->client.username != NULL)
    free(node->client.username);

  if (node->client.user_password != NULL)
    free(node->client.user_password);

  if (node->client.messages) {
    struct message *msg = node->client.messages;
    struct message *tmp;
    while (msg != NULL) {
      tmp = msg;
      msg = msg->next;
      free(tmp->text);
      free(tmp);
    }
  }
  free(node);
}