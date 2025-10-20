#include <database/data_base.h>
#include <database/hashtable/hash_table.h>

int db_push_client(struct data_base *db, struct client *client) {
  return insert_item(db->clients, client, HASH_BY_USERNAME);
}
