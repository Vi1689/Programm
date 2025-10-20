#ifndef MY_ANALYZER__
#define MY_ANALYZER__

#include "database/data_base.h"
#include "error_handler.h"
#include "my_parse/my_parse.h"
#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/**
 * @brief Анализирует сообщение от клиента
 * @param bd Базы данных
 * @param client Клиент
 * @param in Сообщение от клиента
 * @param str Буфер для шутки/Цитаты/Логина и пароля (передаётся для записи)
 * @param size_str Размер буфера
 * @param type Тип ответа (передаётся для записи &)
 * @return 0 - успех, -1 - не получилось.
 */
int analyzer(struct data_base *bd, struct client *client, char *in, char *str,
             size_t size_str, int *type);

/**
 * @brief Записывает нужное сообщение
 * @param type Тип сообщения
 * @param out Сообщение для клиента
 * @param size_out Длина сообщения для клиента
 * @param bd Базы данных
 * @param client Клиент
 * @param str Шутка/Цитат/Логин и пароль
 * @return 0 - успех, -1 - не получилось.
 */
int operation(int type, char *out, size_t size_out, struct data_base *bd,
              struct client *client, char *str);

/**
 * @brief Отправляет историю сообщений
 * @param fd Дискриптор сокета
 * @param sock Структура сокета
 * @param bd Базы данных
 * @param client Клиент
 * @return 0 - успех, -1 - не получилось.
 */
int send_history_mess(int fd, struct sockaddr_in sock, struct data_base *bd,
                      struct client *client);

#endif