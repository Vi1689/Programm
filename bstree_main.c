#include "bstree.h"
#include "hashtab.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    struct listnode* node1;
    hashtab_init(hashtab);
    hashtab_add(hashtab, "Ocelot", 1);
    hashtab_add(hashtab, "Flamingo", 13);
    hashtab_add(hashtab, "Fox", 14);
    node1 = hashtab_lookup(hashtab, "Flamingo");
    if (node1 != NULL)
        printf("Node: %s, %d\n", node1->key, node1->value);
    hashtab_delete(hashtab, "Ocelot");
    node1 = hashtab_lookup(hashtab, "Ocelot");
    if (node1 != NULL)
        printf("Node: %s, %d\n", node1->key, node1->value);
    else
        printf("Node not found\n");
    return 0;
}