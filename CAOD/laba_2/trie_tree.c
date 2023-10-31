#include "trie_tree.h"

struct trie* trie_create()
{
    struct trie* node;
    if ((node = malloc(sizeof(*node))) == NULL) {
        return NULL;
    }
    node->ch = '\0';
    node->value = NULL;
    node->child = NULL;
    node->sibling = NULL;
}

char* trie_lookup(struct trie* root, char* string)
{
    struct trie* node;
    struct trie* list;
    for (list = root; *string != '\0'; ++string) {
        for (node = list; node != NULL; node = node->sibling) {
            if (node->ch == *string) {
                break;
            }
        }
        if (node != NULL) {
            list = node->child;
        } else {
            printf("Такой строчки нет\n");
            return NULL;
        }
    }
    if (node->value) {
        return node->value;
    } else {
        printf("Такой строчки нет\n");
        return NULL;
    }
}

struct trie* trie_insert(struct trie* root, char* string, char* value)
{
    struct trie* node;
    struct trie* parent = NULL;
    struct trie* list = root;
    for (; *string != '\0'; ++string) {
        for (node = list; node != NULL; node = node->sibling) {
            if (node->ch == *string) {
                break;
            }
        }
        if (node == NULL) {
            node = trie_create();
            node->ch = *string;
            node->sibling = list;
            if (parent != NULL) {
                parent->child = node;
            } else {
                root = node;
            }
            list = NULL;
        } else {
            list = node->child;
        }
        parent = node;
    }
    if (node->value != NULL) {
        free(node->value);
    }
    node->value = strdup(value);
    return root;
}

struct trie* trie_delete(struct trie* root, char* string)
{
    int found;
    return trie_delete_dfs(root, NULL, string, &found);
}

struct trie*
trie_delete_dfs(struct trie* root, struct trie* parent, char* value, int* found)
{
    struct trie* node;
    struct trie* prev = NULL;
    *found = (*value == '\0' && root == NULL) ? 1 : 0;
    if (root == NULL || *value == '\0') {
        return root;
    }
    for (node = root; node != NULL; node = node->sibling) {
        if (node->ch == *value) {
            break;
        }
        prev = node;
    }
    if (node == NULL) {
        return root;
    }
    trie_delete_dfs(node->child, node, value + 1, found);
    if (*found > 0 && node->child == NULL) {
        if (prev != NULL) {
            prev->sibling = node->sibling;
        } else {
            if (parent != NULL) {
                parent->child = node->sibling;
            } else {
                root = node->sibling;
            }
        }
        free(node->value);
        free(node);
    }
    node->value = NULL;
    return root;
}

void trie_print(struct trie* root, int level)
{
    struct trie* node = root;
    if (root && root->ch != '\0') {
        printf("%c(%d)", node->ch, level);
        trie_print(node->child, level + 1);
        printf("\n");
        trie_print(node->sibling, level);
    }
}