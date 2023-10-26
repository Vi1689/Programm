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
/*
struct trie* trie_insert(struct trie* root, char* value, char ch)
{
    struct trie* node = root;
    unsigned int l = strlen(value);
    for (int i = 0; i < l; ++i) {
        child = Getchild(node, value[i]);
        if (!child) {
            child = trie_create();
            Setchild(node, value[i], child);
        }
        node = child;
    }
    node->ch = ch;
    return root;
}

struct trie* Getchild(struct trie* root, char value)
{
    if (root->ch == value) {
        if (root->child == NULL) {
            return NULL;
        } else if (root->child->ch == value) {
            return root->child;
        } else if (root->sibling == NULL) {
            return NULL;
        } else {
            return root->sibling;
        }
    } else {
        return root->sibling;
    }
}

void Setchild(struct trie* root, char value, struct trie* child){

}
*/

char* trie_lookup(struct trie* root, char* value)
{
    struct trie* node;
    struct trie* list;
    for (list = root; *value != '\0'; ++value) {
        for (node = list; node != NULL; node = node->sibling) {
            if (node->ch == *value) {
                break;
            }
        }
        if (node != NULL) {
            list = node->child;
        } else {
            return NULL;
        }
    }
    return value;
}

struct trie* trie_insert(struct trie* root, char* value, char ch)
{
    struct trie* node;
    struct trie* parent = NULL;
    struct trie* list = root;
    for (; *value != '\0'; ++value) {
        for (node = list; node != NULL; node = node->sibling) {
            if (node->ch == *value) {
                break;
            }
        }
        if (node == NULL) {
            node = trie_create();
            node->ch = *value;
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

struct trie* trie_delete(struct trie* root, char* value)
{
    int found;
    return trie_delete_dfs(root, NULL, value, &found);
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
    return root;
}