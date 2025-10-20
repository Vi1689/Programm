#include <database/data_base.h>

void destroy_db_fields(struct data_base *db) {
  destroy_hashtable(db->clients);
  destroy_hashtable(db->banlist);
  destroy_expressions(db->funny_jokes);
  destroy_expressions(db->not_funny_jokes);
  destroy_expressions(db->quotes);
  destroy_expressions(db->l_quotes);
}
