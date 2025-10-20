#include <database/client.h>
#include <database/hashtable/hash_table.h>
#include <error_handler.h>
#include <malloc.h>

struct hash_table *create_hashtable(int size) {
  struct hash_table *hashtable = malloc(sizeof(struct hash_table));
  if (!hashtable) {
    ERROR("malloc fail");
    return NULL;
  }
  hashtable->data = malloc(sizeof(struct node) * size);
  if (!hashtable->data) {
    ERROR("malloc fail");
    return NULL;
  }
  hashtable->capacity = size;
  hashtable->size = 0;
  for (int i = 0; i < hashtable->capacity; i++) {
    hashtable->data[i].client.username = NULL;
    hashtable->data[i].client.user_password = NULL;
    hashtable->data[i].client.user_ip_address.s_addr = 0;
    hashtable->data[i].next = NULL;
    hashtable->data[i].client.message_counter = 0;
    hashtable->data[i].client.messages = NULL;
  }
  return hashtable;
}