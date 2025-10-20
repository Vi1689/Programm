#include <database/data_base.h>
#include <database/hashtable/hash_table.h>
#include <malloc.h>

struct client *db_get_client(struct data_base *db, struct client *client) {
  struct node *n = lookup_item(db->clients, client, HASH_BY_USERNAME);
  if (n != NULL) {
    return &n->client;
  }
  return NULL;
}