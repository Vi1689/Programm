#include <database/hashtable/hash_table.h>
#include <database/message.h>
#include <malloc.h>

void destroy_hashtable(struct hash_table *hashtable) {
  for (int i = 0; i < hashtable->capacity; i++) {
    if (hashtable->data[i].client.username != NULL)
      free(hashtable->data[i].client.username);

    if (hashtable->data[i].client.user_password != NULL)
      free(hashtable->data[i].client.user_password);

    if (hashtable->data[i].client.messages) {
      struct message *msg = hashtable->data[i].client.messages;
      struct message *tmp;
      while (msg != NULL) {
        tmp = msg;
        msg = msg->next;
        free(tmp->text);
        free(tmp);
      }
    }

    if (hashtable->data[i].next != NULL) {
      destroy_chain(hashtable->data[i].next);
    }
  }
  free(hashtable->data);
  free(hashtable);
}