#include "bstree.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    struct bstree* tree = bstree_create("ab", 2);
    struct bstree* node;
    bstree_add(tree, "aa", 1);
    bstree_add(tree, "bb", 3);
    node = bstree_lookup(tree, "bb");
    printf("key %s: %d\n", node->key, node->value);
    node = bstree_delete(tree, "aa");
    node = bstree_min(tree);
    printf("Min key %s: %d\n", node->key, node->value);
    bstree_add(tree, "aa", 1);
    node = bstree_min(tree);
    printf("key %s: %d\n", node->key, node->value);
    return 0;
}