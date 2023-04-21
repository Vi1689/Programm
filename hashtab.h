#ifndef __HASHTAB__
#define __HASHTAB__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum { HASHTAB_SIZE = 200000 };

struct listnode {
    char* key;
    int value;
    struct listnode* next;
};
//unsigned int hashtab_hash(char* key);
unsigned int hashtab_hash(char* key);
void hashtab_init(struct listnode** hashtab);
void hashtab_add(struct listnode** hashtab, char* key, int value, unsigned int* arr, unsigned int i);
struct listnode* hashtab_lookup(struct listnode** hashtab, char* key);
void hashtab_delete(struct listnode** hashtab, char* key);

#endif