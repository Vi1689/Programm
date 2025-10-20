#ifndef MY_PARSE__
#define MY_PARSE__

#include "database/data_base.h"
#include "error_handler.h"
#include <ctype.h>
#include <malloc.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Типы токенов
 */
enum TYPE {
  CHAT,       // ** Токен команды /chat */
  BAN,        // ** Токен бана */
  ERROR,      // ** Токен ошибки */
  MISSPELL,   // ** Токен орфографической ошибки */
  HELP,       // ** Токен команды /help */
  INFO,       // ** Токен команды /info */
  JOKE,       // ** Токен команды /joke */
  QUOTE,      // ** Токен команды /quote */
  NEW,        // ** Токен команды new */
  LOGIN,      // ** Токен команды /login */
  PASSWORD,   // ** Токен команды /password */
  REGISTR,    // ** Токен регистрации */
  COME,       // ** Токен авторизации */
  TEXT,       // ** Токен текста */
  END,        // ** Завершающий токен */
  FUNNY,      // ** Токен команды funny */
  NOT_FUNNY,  // ** Токен команды not_funny */
  SCIENCE,    // ** Токен команды science */
  LIT,        // ** Токен команды literature */
  UPDATA,     // ** Токен запроса на обновление */
  PUSH_FUNNY, // ** Токен записи смешной шутки */
  PUSH_NOT_FUNNY, // ** Токен записи не смешной шутки */
  PUSH_SCIENCE,   // ** Токен записи научной цитаты */
  PUSH_LIT // ** Токен записи литературной цитаты*/
};

struct token {
  int type;
  char str[256];
};

struct parse {
  size_t size;
  struct token *set_token;
};

/**
 * @brief Создаёт массив для токенов
 * @return Указатель на начало - успех, NULL - не получилось.
 */
struct parse *create_arr_tok();

/**
 * @brief Проверяет строку на запрещенные символы
 * @param str Проверяемая строка
 * @return 0 - успех, -1 - не получилось.
 */
int prohibited_symbol(const char *str);

/**
 * @brief Разбивает строку на токены
 * @param str Разбиваемая строка
 * @param a Массив токенов
 * @return 0 - успех, -1 - не получилось.
 */
int splitting_into_tokens(char *str, struct parse *a);

/**
 * @brief Добавление токена
 * @param a Массив токенов
 * @param tok Токен
 * @return 0 - успех, -1 - не получилось.
 */
int add_token(struct parse *a, struct token tok);

/**
 * @brief Чтение токена
 * @param a Массив токенов
 * @param current_token Текущий токен
 * @param tmp Токен (передаётся для записи &)
 * @return 0 - успех, -1 - не получилось.
 */
int read_token(struct parse *a, size_t current_token, struct token *tmp);

/**
 * @brief Следующий токен
 * @param current_token Текущий токен (передаётся для записи &)
 */
void next_token(size_t *current_token);

/**
 * @brief Первая проверка токенов
 * @param a Массив токенов
 * @param type Тип ответа (передаётся для записи &)
 * @param str Шутка/Цитата/Логин и пароль
 * @return 0 - успех, -1 - не получилось.
 */
int step_1(struct parse *a, int *type, char *str);

/**
 * @brief Вторая проверка токенов
 * @param a Массив токенов
 * @param current_token Текущий токен
 * @param old_tok Предыдуший токен
 * @param tok Текущий токен
 * @param type Тип ответа (передаётся для записи &)
 * @param str Шутка/Цитата/Логин и пароль
 * @return 0 - успех, -1 - не получилось.
 */
int step_2(struct parse *a, size_t current_token, int old_tok, int tok,
           int *type, char *str);

/**
 * @brief Третья проверка токенов
 * @param a Массив токенов
 * @param current_token Текущий токен
 * @param old_tok Предыдуший токен
 * @param tok Текущий токен
 * @param type Тип ответа (передаётся для записи &)
 * @param str Шутка/Цитата/Логин и пароль
 * @return 0 - успех, -1 - не получилось.
 */
int step_3(struct parse *a, size_t current_token, int old_tok, int tok,
           int *type, char *str);

/**
 * @brief Авторизация клиента
 * @param a Массив токенов
 * @param current_token Текущий токен
 * @param login Логин
 * @param password Пароль
 * @param str Шутка/Цитата/Логин и пароль
 * @param type Тип ответа (передаётся для записи &)
 * @return 0 - успех, -1 - не получилось.
 */
int authorization(struct parse *a, size_t current_token, char *login,
                  char *password, char *str, int *type);

/**
 * @brief Регистрация клиента
 * @param a Массив токенов
 * @param current_token Текущий токен
 * @param login Логин
 * @param password Пароль
 * @param str Шутка/Цитата/Логин и пароль
 * @param type Тип ответа (передаётся для записи &)
 * @return 0 - успех, -1 - не получилось.
 */
int registration(struct parse *a, size_t current_token, char *login,
                 char *password, char *str, int *type);

/**
 * @brief Чтение токена
 * @param a Массив токенов
 * @param current_token Текущий токен
 * @param str Текст в сообщении
 * @return 0 - успех, -1 - не получилось.
 */
int read_text(struct parse *a, size_t current_token, char *str);

/**
 * @brief Удаляет массив токенов
 * @param tmp Массив токенов
 */
void delete_arr_tok(struct parse *tmp);

#endif