#include <database/hashtable/hash_table.h>

int djb2_hash(char *str) {
  int hash = 5381;
  int c;
  while ((c = *str++))
    hash = ((hash << 5) + hash) + c;
  if (hash < 0)
    hash *= -1;
  return hash;
}