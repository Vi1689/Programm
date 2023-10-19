#pragma once

#include <stdio.h>
#include <stdlib.h>

struct rbtree {
    int key;
    char* value;
    // 0 - red
    // 1 - black
    char color;
    struct rbtree* left;
    struct rbtree* right;
    struct rbtree* parent;
};



void rbtree_Add_Fixup(struct rbtree* tree, struct rbtree* z);
void LeftRotate(struct rbtree* x);
void RightRotate(struct rbtree* x);
struct rbtree* rbtree_create(int key, char* value);
struct rbtree* rbtree_add(struct rbtree* tree, int key, char* value);
struct rbtree* rbtree_lookup(struct rbtree* tree, int key);
struct rbtree* rbtree_delete(struct rbtree* tree, int key);
struct rbtree* rbtree_min(struct rbtree* tree);
struct rbtree* rbtree_max(struct rbtree* tree);
void RBTreeTransplant(struct rbtree* tree, struct rbtree* u, struct rbtree* v);
void rbtree_delete_Fixup(
        struct rbtree* tree, struct rbtree* x, struct rbtree* z);
void rbtree_free(struct rbtree* tree);
void obxod(struct rbtree* tree);
void rbtree_print_dfs(struct rbtree* tree, int level);
struct rbtree* root(struct rbtree* tree);