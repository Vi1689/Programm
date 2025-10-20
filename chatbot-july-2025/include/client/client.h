#pragma once

#include <arpa/inet.h>
#include <errno.h>
#include <error_handler.h>
#include <my_network/my_network.h>
#include <ncurses.h>
#include <netinet/in.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <ui/ui.h>
#include <unistd.h>

#define SERVER_PORT 8080
#define CLIENT_PORT 7777
#define SERVER_ADDRESS "172.18.0.1"

/**
 * @brief Структура для хранения и отправки на сервер сообщения клиента.
 * @param user_login Логин пользователя, чье сообщение хранится в структуре
 * @param message Сообщение пользователя, которое он отправил чат-боту
 */
struct client_message {
  char user_login[32];
  char message[512];
};

/**
 * @brief Отправляет сообщение на сервер и получает ответ.
 * @param message Указатель на структуру с логином и сообщением клиента.
 * @return Указатель на строку с ответом сервера, либо NULL при ошибке.
 */
char *send_message_to_server(char *messasge, int client_fd);

/**
 * @brief Запускает клиента, авторизацию и чат.
 * @param client_port Порт клиента.
 * @param ip_address IP-адрес клиента.
 * @return 0 при успехе, -1 при ошибке.
 */
int start_client(int client_port, char *ip_address);