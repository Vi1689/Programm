#pragma once

/**
 * @brief Структура хранящая какоелибо выражения(шутка, цитата).
 */
struct expression {
  char *expression; /**Строка с выражением. */
  int len;          /**Длина строки с выражением. */
  struct client *owner; /**Указатель на владельца выражениея*/
};

/**
 * @brief Структура хранящая выражения.
 */
struct expressions {
  struct expression *arr; /**Массив выражений. */
  int size;               /**Количество выражений. */
  int capacity; /**Ёмкость массива выражений. */
};
