#pragma once

#include "client/client.h"
#include <ctype.h>
#include <form.h>
#include <ncurses.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Запускает интерфейс авторизации и возвращает учетные данные.
 * @return Код завершения: 0 в случае успеха, иначе ненулевое значение.
 */
int start_ui_auth();

/**
 * @brief Запускает интерфейс чата.
 * @param client_fd Дескриптор файла клиента для связи с сервером.
 * @return Код завершения: 0 в случае успеха, иначе ненулевое значение.
 */
int start_ui_chat(int client_fd, int num_of_messages);