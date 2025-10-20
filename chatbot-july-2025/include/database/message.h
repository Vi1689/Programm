#pragma once
/**
 * @brief Структура хранящая сообщение.
 */
struct message {
  char *text;
  struct message *next;
};