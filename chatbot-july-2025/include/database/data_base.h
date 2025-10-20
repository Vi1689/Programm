#pragma once
#include <database/client.h>
#include <database/expression.h>
#include <database/hashtable/hash_table.h>
#include <database/message.h>

/**
 * HT_LEN - Ёмкость хеш-таблицы(обязательно
 * должна быть больше чем предпологаемое кол-во
 * клиентов, во избежании коллизий).
 */
#define HT_LEN 100

#define AMOUNT_OF_FUNNY_JOKES 5
#define AMOUNT_OF_NOT_FUNNY_JOKES 5
#define AMOUNT_OF_QUOTES 3

/**
 * Макросы, кончающиеся на _TYPE, нужны для
 * выбора загружаемых данных в структуры
 * expressions
 */
#define FUNNY_JOKES_TYPE 1
#define NOT_FUNNY_JOKES_TYPE 2
#define SCIENTIFIC_QUOTES_TYPE 3
#define LITERARY_QUOTES_TYPE 4

/**
 * @brief Структура базы данных.
 */
struct data_base {
  struct hash_table *clients;
  struct hash_table *banlist;
  struct expressions *funny_jokes;
  struct expressions *not_funny_jokes;
  struct expressions *quotes;   /*Научные цитаты*/
  struct expressions *l_quotes; /*Литературные цитаты*/
};

/**
 * @brief Выделяет память под базу данных.
 * @return Возвращает указатель на нее.
 */
struct data_base *db_create(void);

/**
 * @brief Удаляет базу данных.
 * @param db Указатель на структуру базы данных.
 */
void db_destroy(struct data_base *db);

/**
 * @brief Добавляет нового клиента в табицу.
 * @param db Указатель на структуру базы данных.
 * @param client Указатель на структуру client с которой скопируются данные.
 * @return 0 - успех, 1 - не получилось.
 */
int db_push_client(struct data_base *db, struct client *client);

/**
 * @brief Удаляет клиента из таблицы.
 * @param db Указатель на структуру базы данных.
 * @param client Указатель на структуру client по которой будет поиск.
 * @return 0 - успех, 1 - не получилось.
 */
int db_pop_client(struct data_base *db, struct client *client);

/**
 * @brief Проверяет наличие клиента в таблице.
 * @param db Указатель на структуру базы данных.
 * @param client Указатель на структуру client по которой будет поиск.
 * @return 1 - клиент есть в таблице, 0 - клиента нет в таблице.
 */
int db_lookup_client(struct data_base *db, struct client *client);

/**
 * @brief Выдает структуру клиента, по имени.
 * @param db Указатель на структуру базы данных.
 * @param client Указатель на структуру client по которой будет поиск.
 * @return Указатель на структуру client. NULL если пользователя с таким именем
 */
struct client *db_get_client(struct data_base *db, struct client *client);

/**
 * @brief Повышает wrong_command_counter клиента, по имени.
 * @param db Указатель на структуру базы данных.
 * @param client Указатель на структуру client по которой будет поиск.
 * @return 0 - успех, 1 - не получилось.
 */
int db_increase_wrong_counter(struct data_base *db, struct client *client);

/**
 * @brief Выдаёт выражение в зависимости от типа.
 * @param db Указатель на структуру базы данных.
 * @param client Указатель на структуру client по которой будет доступ.
 * @param type Макрос указывающий на тип выражений(jokes, quotes...).
 * @note Если параметр client будет NULL то шутки будут выбираться серверные.
 * @return Структуру expression.
 */
struct expression *db_get_expression(struct data_base *db,
                                     struct client *client, int type);

/**
 * @brief Перемещает клиента в банлист.
 * @param db Указатель на структуру базы данных.
 * @param client Указатель на структуру client по которой будет поиск.
 * @return 0 - успех, 1 - не получилось.
 */
int db_ban_client(struct data_base *db, struct client *client);

/**
 * @brief Ищет клиента в банлисте.
 * @param db Указатель на структуру базы данных.
 * @param client Указатель на структуру client по которой будет поиск.
 * @return 0 - такого клиента нет, либо он не в бане, 1 - забанен.
 */
int db_is_client_banned(struct data_base *db, struct client *client);

/**
 * @brief Добавляет новое выражение.
 * @param db Указатель на структуру базы данных.
 * @param expr Указатель на структуру expression с которой скопируются данные.
 * @param type Макрос указывающий на тип выражений(jokes, quotes...).
 * @return 0 - успех, 1 - не получилось.
 */
int db_push_expression(struct data_base *db, struct expression *expr, int type);

/**
 * @brief Добавляет в структуру пользователя сообщение.
 * @param db Указатель на структуру базы данных.
 * @param client Указатель на структуру client по которой будет поиск.
 * @param text Строка с текстом сообщения.
 * @return 0 - успех, 1 - не получилось.
 */
int db_push_message(struct data_base *db, struct client *client, char *text);

/**
 * @brief Выдаёт историю сообщений.
 * @param db Указатель на структуру базы данных.
 * @param client Указатель на структуру client по которой будет поиск.
 * @return Указатель на начало списка сообщений.
 */
struct message *db_get_messages(struct data_base *db, struct client *client);

//------------Ниже служебные функции------------

/**
 * @brief Создаёт и инициализирует структуру expressions.
 * @param size Длина массива под выражения.
 * @return Указатель на созданную структуру
 */
struct expressions *create_expressions(int size);

/**
 * @brief Освобождает структуру expressions.
 * @param expr Указаткль на структуру expressoins.
 */
void destroy_expressions(struct expressions *expr);

/**
 * @brief Загружает выражения из файла.
 * @param expr Указаткль на структуру expressoins в которую загружать выражения.
 * @param type Макрос указывающий на тип выражений(jokes, quotes...).
 * @return 0 - успех, 1 - не получилось.
 */
int load_expressions(struct expressions *expr, int type);

/**
 * @brief Освобождает поля структуры data_base.
 * @param db Указаткль на базу данных.
 */
void destroy_db_fields(struct data_base *db);