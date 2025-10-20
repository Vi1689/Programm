#pragma once
#include <database/message.h>
#include <net/ethernet.h>
#include <netinet/in.h>

#define MAX_CLIENTS_IPS 20

/**
 * @brief Структура, предназначенная для хранения связок ip и счётчик
 * неправильных команд.
 */
struct ip_n_counter {
  in_addr_t ip;
  int counter;
};

/**
 * @brief Структура для хранения информации о клиенте.
 */
struct client {
  char *username;
  char *user_password;
  struct in_addr user_ip_address;
  struct ether_addr user_mac_address;
  unsigned short int wrong_command_counter;
  struct ip_n_counter clients_ips[MAX_CLIENTS_IPS];
  struct message *messages;
  int message_counter;
};