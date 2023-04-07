#include "bstree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct bstree* bstree_create(char* key, int value)
{
    struct bstree* node = malloc(sizeof(*node));
    if (node) {
        node->key = key;
        node->value = value;
        node->left = NULL;
        node->right = NULL;
    }
    return node;
}

void bstree_add(struct bstree* tree, char* key, int value)
{
    if (!tree) {
        return;
    }
    struct bstree* parent;
    struct bstree* node;
    while (tree != NULL) {
        parent = tree;
        if (strcmp(key, tree->key) < 0) {
            tree = tree->left;
        } else if (strcmp(key, tree->key) > 0) {
            tree = tree->right;
        } else {
            return;
        }
    }
    node = bstree_create(key, value);
    if (strcmp(key, parent->key) < 0) {
        parent->left = node;
    } else {
        parent->right = node;
    }
}

struct bstree* bstree_lookup(struct bstree* tree, char* key)
{
    while (tree != NULL) {
        if (strcmp(key, tree->key) == 0) {
            return tree;
        } else if (strcmp(key, tree->key) < 0) {
            tree = tree->left;
        } else {
            tree = tree->right;
        }
    }
    return tree;
}

struct bstree* bstree_delete(struct bstree* tree, char* key)
{
    struct bstree* parent = NULL;
    struct bstree* node = tree;
    while (node != NULL && node->key != key) {
        parent = node;
        if (strcmp(key, node->key) < 0) {
            node = node->left;
        } else {
            node = node->right;
        }
    }
    if (!node) {
        return tree;
    }
    if (!(node->left)) {
        bestree_replanse(parent, node, node->right);
        if (!parent) {
            tree = node->right;
        }
    } else if (!(node->right)) {
        bestree_replanse(parent, node, node->left);
        if (!parent) {
            tree = node->left;
        }
    } else {
        struct bstree* min = node->right;
        struct bstree* minparent = min;
        while (min->left != NULL) {
            minparent = min;
            min->left;
        }
        bestree_replanse(parent, node, min);
        if (!parent) {
            tree = min;
        }
        if (node->right != min) {
            minparent->left = min->right;
            min->left = node->left;
            min->right = node->right;
        } else {
            min->left = node->left;
        }
    }
    free(node);
    return tree;
}

void bestree_replanse(
        struct bstree* parent, struct bstree* node, struct bstree* child)
{
    if (parent) {
        if (strcmp(node->key, parent->key) < 0) {
            parent->left = child;
        } else {
            parent->right = child;
        }
    }
}

struct bstree* bstree_min(struct bstree* tree)
{
    if (!tree) {
        return NULL;
    }
    while (tree->left != NULL) {
        tree = tree->left;
    }
    return tree;
}

struct bstree* bstree_max(struct bstree* tree)
{
    if (!tree) {
        return NULL;
    }
    while (tree->right != NULL) {
        tree = tree->right;
    }
    return tree;
}