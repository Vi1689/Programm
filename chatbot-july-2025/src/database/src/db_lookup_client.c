#include <database/data_base.h>
#include <database/hashtable/hash_table.h>

int db_lookup_client(struct data_base *db, struct client *client) {
  struct node *n = lookup_item(db->clients, client, HASH_BY_USERNAME);
  if (!n) {
    return 0;
  }
  return 1;
}
