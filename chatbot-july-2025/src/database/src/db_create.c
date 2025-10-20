#include <database/data_base.h>
#include <database/hashtable/hash_table.h>
#include <error_handler.h>
#include <malloc.h>

struct data_base *db_create(void) {
  struct data_base *db = malloc(sizeof(struct data_base));
  if (!db) {
    ERROR("malloc fail");
    return NULL;
  }
  db->clients = create_hashtable(HT_LEN);
  db->banlist = create_hashtable(HT_LEN);
  db->funny_jokes = create_expressions(AMOUNT_OF_FUNNY_JOKES);
  db->not_funny_jokes = create_expressions(AMOUNT_OF_NOT_FUNNY_JOKES);
  db->quotes = create_expressions(AMOUNT_OF_QUOTES);
  db->l_quotes = create_expressions(AMOUNT_OF_QUOTES);

  if (load_expressions(db->funny_jokes, FUNNY_JOKES_TYPE)) {
    destroy_db_fields(db);
    ERROR("load funny jokes fail");
    return NULL;
  }
  if (load_expressions(db->not_funny_jokes, NOT_FUNNY_JOKES_TYPE)) {
    destroy_db_fields(db);
    ERROR("load not funny jokes fail");
    return NULL;
  }
  if (load_expressions(db->quotes, SCIENTIFIC_QUOTES_TYPE)) {
    destroy_db_fields(db);
    ERROR("load quotes fail");
    return NULL;
  }
  if (load_expressions(db->l_quotes, LITERARY_QUOTES_TYPE)) {
    destroy_db_fields(db);
    ERROR("load quotes fail");
    return NULL;
  }

  return db;
}