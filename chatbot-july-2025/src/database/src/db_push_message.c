#include <database/data_base.h>
#include <database/hashtable/hash_table.h>
#include <error_handler.h>
#include <malloc.h>
#include <string.h>
int db_push_message(struct data_base *db, struct client *client, char *text) {
  if (text == NULL) {
    return 1;
  }
  struct node *n = lookup_item(db->clients, client, HASH_BY_USERNAME);
  if (n == NULL) {
    return 1;
  }
  if (n->client.messages == NULL) {
    n->client.messages = malloc(sizeof(struct message));
    if (n->client.messages == NULL) {
      ERROR("malloc fail");
      return 1;
    }
    n->client.messages->text = strdup(text);
    n->client.messages->next = NULL;
  } else {
    struct message *msg = n->client.messages;
    while (msg->next != NULL) {
      msg = msg->next;
    }

    msg->next = malloc(sizeof(struct message));
    if (n->client.messages == NULL) {
      ERROR("malloc fail");
      return 1;
    }
    msg = msg->next;
    msg->next = NULL;
    msg->text = strdup(text);
  }

  n->client.message_counter++;
  return 0;
}
