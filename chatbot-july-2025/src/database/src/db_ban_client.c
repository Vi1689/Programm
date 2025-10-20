#include <database/data_base.h>
#include <database/hashtable/hash_table.h>
#include <error_handler.h>

int db_ban_client(struct data_base *db, struct client *client) {
  struct node *n = lookup_item(db->clients, client, HASH_BY_USERNAME);
  if (!n) {
    return 1;
  }
  if (insert_item(db->banlist, &(n->client), HASH_BY_IP)) {
    ERROR("ht insert fail");
    return 1;
  }
  return 0;
}
