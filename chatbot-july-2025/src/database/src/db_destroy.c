#include <database/data_base.h>
#include <malloc.h>

void db_destroy(struct data_base *db) {
  destroy_db_fields(db);
  free(db);
}
