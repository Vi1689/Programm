#include <stdio.h>
#include <stdlib.h>

struct bstree {
    int key; // Ключ
    char* value; // Значение
    struct bstree *left;
    struct bstree *right;
};