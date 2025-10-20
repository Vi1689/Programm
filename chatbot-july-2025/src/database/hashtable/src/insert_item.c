#include <arpa/inet.h>
#include <database/client.h>
#include <database/hashtable/hash_table.h>
#include <error_handler.h>
#include <malloc.h>
#include <string.h>

int fill_item(struct node *n, struct client *client) {
  if (client->username != NULL) {
    n->client.username = malloc(sizeof(char) * (strlen(client->username) + 1));
    if (!n->client.username) {
      ERROR("malloc fail");
      return 1;
    }
    strcpy(n->client.username, client->username);
  }
  if (client->user_password != NULL) {
    n->client.user_password =
        malloc(sizeof(char) * (strlen(client->user_password) + 1));
    if (!n->client.user_password) {
      if (n->client.username != NULL)
        free(n->client.username);
      ERROR("malloc fail");
      return 1;
    }
    strcpy(n->client.user_password, client->user_password);
  }
  for (int i = 0; i < MAX_CLIENTS_IPS; i++) {
    n->client.clients_ips[i].counter = 0;
    n->client.clients_ips[i].ip = 0;
  }
  n->client.wrong_command_counter = client->wrong_command_counter;
  n->client.user_ip_address = client->user_ip_address;
  n->client.user_mac_address = client->user_mac_address;
  n->client.clients_ips[0].ip = client->user_ip_address.s_addr;
  n->client.message_counter = 0;
  n->client.messages = NULL;
  return 0;
}

int insert_item(struct hash_table *hashtable, struct client *client, int flag) {
  int hash;
  if (flag)
    hash = djb2_hash(client->username);
  else
    hash = djb2_hash(inet_ntoa(client->user_ip_address));
  struct node *n = &(hashtable->data[hash % hashtable->capacity]);
  if (n->client.user_ip_address.s_addr == 0 && n->next == NULL) {
    if (fill_item(n, client)) {
      ERROR("fill item fail");
      return 1;
    }
  } else {
    while (n->next != NULL) {
      n = n->next;
    }
    n->next = malloc(sizeof(struct node));
    if (!n->next) {
      ERROR("malloc fail");
      return 1;
    }
    n = n->next;
    if (fill_item(n, client)) {
      free(n);
      ERROR("fill item fail");
      return 1;
    }
    n->next = NULL;
  }
  hashtable->size++;
  return 0;
}