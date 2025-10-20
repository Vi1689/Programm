#pragma once

#include "ui.h"
#include <pthread.h>

#define TITLE "Chat-bot Eltex"
#define SIDEBAR_W 20
#define INPUT_H 3
#define MAX_MESSAGES 100
#define MSG_WIDTH 64

/**
 * @brief Структура для хранения и отображения сообщений в чате.
 */
typedef struct {
  char text[256];
  bool from_bot;
} Message;

/**
 * @brief Структура для хранения информации об отображении текущего чата.
 */
typedef struct {
  int pad_pos;
  int msg_count;
  int max_pos;
  Message messages[MAX_MESSAGES];
} ChatContext;

/**
 * @brief Типы возвращаемых значений при завершении чата
 */
typedef enum {
  CHAT_SUCCESS = 0, // Успешный выход из чата
  CHAT_ERROR = -1,  //  Ошибка во время работы чата
  CHAT_BANNED = -2 // Пользователя забанили во время работы чата
} ChatExitCode;

/**
 * @brief Выводит историю сообщений клиента
 * @param client_fd Дескриптор файла клиента для взаимодействия с сервером.
 * @param num_of_messages Количество сообщений в истории сообщений
 * @param chat_context Cтруктура для хранения информации об отображении текущего
 * чата.
 * @return Код завершения: 0 в случае успеха, иначе ненулевое значение.
 */
int print_history_of_messages(int client_fd, int num_of_messages,
                              ChatContext *chat_context);

/**
 * @brief Отправляет запросы серверу на обновление истории чата
 * @param arg Указатель на аргумент потока.
 * @return NULL.
 */
void *pthread_get_update(void *arg);

/**
 * @brief Добавляет новое сообщение в чат и обновляет связанные параметры.
 * @param text Указатель на текст сообщения.
 * @param from_bot Флаг, указывающий, отправлено ли сообщение ботом (true) или
 * пользователем (false).
 * @param msg_count Указатель на счётчик сообщений в чате.
 * @param pad_pos Указатель на позицию прокрутки области чата.
 * @param messages Массив структур Message для хранения сообщений.
 * @return Код завершения: 0 в случае успеха, иначе ненулевое значение.
 */
int add_message(char *text, bool from_bot, ChatContext *chat_context);

/**
 * @brief Создаёт и настраивает окна интерфейса чата.
 * @param win_title Указатель на указатель на окно заголовка.
 * @param win_sidebar Указатель на указатель на окно боковой панели.
 * @param win_input Указатель на указатель на окно поля ввода.
 * @param pad_chat Указатель на указатель на область чата (pad).
 * @return Код завершения: 0 в случае успеха, иначе ненулевое значение.
 */
int create_windows(WINDOW **win_title, WINDOW **win_sidebar, WINDOW **win_input,
                   WINDOW **pad_chat);

/**
 * @brief Рисует рамку сообщения в области чата с заданным текстом.
 * @param pad Указатель на область чата (pad).
 * @param y Координата Y для начала отрисовки сообщения.
 * @param x Координата X для начала отрисовки сообщения.
 * @param text Указатель на текст сообщения.
 * @param from_bot Флаг, указывающий, от бота ли сообщение (true) или от
 * пользователя (false).
 * @return Код завершения: 0 в случае успеха, иначе ненулевое значение.
 */
int draw_message_box(WINDOW *pad, int y, int x, const char *text,
                     bool from_bot);

/**
 * @brief Инициализирует цветовые пары для оформления чата.
 * @return Код завершения: 0 в случае успеха, иначе ненулевое значение.
 */
int init_colors_chat();

/**
 * @brief Перерисовывает все сообщения в области чата.
 * @param msg_count Количество сообщений в чате.
 * @param pad_pos Указатель на текущую позицию прокрутки области чата.
 * @param messages Массив структур Message с данными сообщений.
 */
void redraw_messages(ChatContext *chat_context);

/**
 * @brief Обновляет прокрутку области чата.
 * @param pad_pos Указатель на текущую позицию прокрутки.
 */
void refresh_pad(int *pad_pos);

/**
 * @brief Запускает цикл обработки ввода пользователя в чате.
 * @param win_input Указатель на окно поля ввода.
 * @param client_fd Дескриптор файла клиента для взаимодействия с сервером.
 * @return Код завершения: CHAT_SUCCESS в случае успеха, CHAT_ERROR - в случае
 * ошибки, CHAT_BANNED - в случае блокировки пользователя.
 */
int run_chat_loop(WINDOW *win_input, int client_fd, int num_of_messages);