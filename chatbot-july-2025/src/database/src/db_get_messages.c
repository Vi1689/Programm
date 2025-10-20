#include <database/data_base.h>
#include <database/hashtable/hash_table.h>
#include <string.h>
struct message *db_get_messages(struct data_base *db, struct client *client) {
  struct node *n = lookup_item(db->clients, client, HASH_BY_USERNAME);
  if (n == NULL) {
    return NULL;
  }
  return n->client.messages;
}
