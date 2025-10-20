#include <database/data_base.h>
#include <database/hashtable/hash_table.h>

int db_is_client_banned(struct data_base *db, struct client *client) {
  struct node *n = lookup_item(db->banlist, client, HASH_BY_IP);
  if (!n) {
    return 0;
  }
  return 1;
}
