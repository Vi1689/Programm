#include <arpa/inet.h>
#include <database/client.h>
#include <database/hashtable/hash_table.h>
#include <string.h>

int find_ip(struct ip_n_counter *arr, short unsigned int *counter,
            in_addr_t ip) {
  for (int i = 0; i < MAX_CLIENTS_IPS; i++) {
    if (arr[i].ip == ip) {
      *counter = arr[i].counter;
      return 0;
    }
  }
  return 1;
}

void place_new_ip(struct ip_n_counter *arr, in_addr_t ip) {
  for (int i = 0; i < MAX_CLIENTS_IPS; i++) {
    if (arr[i].ip == 0 && arr[i].counter == 0) {
      arr[i].ip = ip;
      arr[i].counter = 0;
      return;
    }
  }
}

void update_counter(struct ip_n_counter *arr, in_addr_t ip, int cur_counter) {
  for (int i = 0; i < MAX_CLIENTS_IPS; i++) {
    if (arr[i].ip == ip) {
      arr[i].counter = cur_counter;
      return;
    }
  }
}

struct node *lookup_item(struct hash_table *hashtable, struct client *client,
                         int flag) {
  int hash;
  if (flag)
    hash = djb2_hash(client->username);
  else
    hash = djb2_hash(inet_ntoa(client->user_ip_address));

  struct node *n = &(hashtable->data[hash % hashtable->capacity]);
  if (!flag) {
    do {
      if (n->client.user_ip_address.s_addr == client->user_ip_address.s_addr) {
        return n;
      }
      n = n->next;
    } while (n != NULL);
  } else {
    do {
      if (n->client.username) {
        if (!strcmp(n->client.username, client->username)) {
          //если клиент зашел с другого ip
          if (n->client.user_ip_address.s_addr !=
              client->user_ip_address.s_addr) {
            //чистка массива от забаненых ip адресов
            for (int i = 0; i < MAX_CLIENTS_IPS; i++) {
              if (n->client.clients_ips[i].counter == 3) {
                n->client.clients_ips[i].counter = 0;
                n->client.clients_ips[i].ip = 0;
              }
            }
            //записываем счётчик неверных команд к прошлому ip
            for (int i = 0; i < MAX_CLIENTS_IPS; i++) {
              if (n->client.clients_ips[i].ip ==
                  n->client.user_ip_address.s_addr) {
                n->client.clients_ips[i].counter =
                    n->client.wrong_command_counter;
                break;
              }
            }
            //сначала ищем новый ip, если его нет, то вставляем в массив и
            //зануляем счётчик
            if (find_ip(&(n->client.clients_ips[0]),
                        &(n->client.wrong_command_counter),
                        client->user_ip_address.s_addr)) {
              place_new_ip(&(n->client.clients_ips[0]),
                           client->user_ip_address.s_addr);
              n->client.wrong_command_counter = 0;
            }

            n->client.user_ip_address = client->user_ip_address;
          } else {
            update_counter(&(n->client.clients_ips[0]),
                           n->client.user_ip_address.s_addr,
                           n->client.wrong_command_counter);
          }
          return n;
        }
      }
      n = n->next;
    } while (n != NULL);
  }
  return NULL;
}
