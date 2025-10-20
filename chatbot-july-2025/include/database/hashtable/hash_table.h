#pragma once
#include <database/client.h>

#define HASH_BY_USERNAME 1
#define HASH_BY_IP 0

struct node {
  struct client client;
  struct node *next;
};

struct hash_table {
  struct node *data;
  int size;
  int capacity;
};

struct hash_table *create_hashtable(int size);
void destroy_hashtable(struct hash_table *hashtable);
void destroy_chain(struct node *node);
int insert_item(struct hash_table *hashtable, struct client *client, int flag);
struct node *lookup_item(struct hash_table *hashtable, struct client *client,
                         int flag);
int delete_item(struct hash_table *hashtable, struct client *client, int flag);
int djb2_hash(char *str);