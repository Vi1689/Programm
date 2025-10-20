#include <arpa/inet.h>
#include <database/client.h>
#include <database/hashtable/hash_table.h>
#include <malloc.h>
#include <string.h>

int delete_item(struct hash_table *hashtable, struct client *client, int flag) {
  int hash;
  if (flag)
    hash = djb2_hash(client->username);
  else
    hash = djb2_hash(inet_ntoa(client->user_ip_address));
  int index = hash % hashtable->capacity;

  struct node *n = &(hashtable->data[index]);
  struct node *prev_n = n;
  struct node *next_n = n;

  if (n->client.user_ip_address.s_addr == 0 && n->next == NULL) {
    return 1;
  }
  if (n->client.user_ip_address.s_addr != 0 && n->next == NULL) {
    if (n->client.user_ip_address.s_addr != client->user_ip_address.s_addr) {
      return 1;
    }
    if (n->client.username != NULL) {
      free(n->client.username);
      n->client.username = NULL;
    }
    if (n->client.user_password != NULL) {
      free(n->client.user_password);
      n->client.user_password = NULL;
    }
    n->client.user_ip_address.s_addr = 0;
    n->next = NULL;
    hashtable->size--;
    return 0;
  }

  while (next_n != NULL) {
    prev_n = n;
    n = n->next;
    next_n = n->next;
    if (n->client.user_ip_address.s_addr == client->user_ip_address.s_addr) {
      prev_n->next = next_n;
      if (n->client.username != NULL)
        free(n->client.username);
      if (n->client.user_password != NULL)
        free(n->client.user_password);
      free(n);
      hashtable->size--;
      return 0;
    }
  }
  return 1;
}