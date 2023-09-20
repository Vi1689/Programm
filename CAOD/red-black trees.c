#include <red-black trees.h>

struct rbtree* bstree_create(int key, char* value)
{
    struct rbtree* node = malloc(sizeof(*node));
    if (node) {
        node->key = key;
        node->value = value;
        node->color = '1';
        node->left = NULL;
        node->right = NULL;
        node->parent = NULL;
    }
    return node;
}

struct rbtree* rbtree_add(struct rbtree* tree, int key, char* value)
{
    if (!tree) {
        return;
    }
    struct rbtree* parent;
    struct rbtree* node;
    while (tree != NULL) {
        parent = tree;
        if (key < tree->key) {
            tree = tree->left;
        } else if (key > tree->key) {
            tree = tree->right;
        } else {
            return;
        }
    }
    node = bstree_create(key, value);
    node->parent = parent;
    if (key < node->parent->key) {
        node->parent->key = node;
    } else {
        node->parent->key = node;
    }
    node->color = '0';
    rbtree_Add_Fixup(tree, node);
}

void LeftRotate(struct rbtree* x)
{
    struct rbtree* y = x->right;
    x->right = y->left;
    if (y->left != NULL) {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}

void RightRotate(struct rbtree* x)
{
    struct rbtree* y = x->left;
    x->left = y->right;
    if (y->right != NULL) {
        y->right->parent = x;
    }
    y->parent = x->parent;
    if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }
    y->right = x;
    x->parent = y;
}

void rbtree_Add_Fixup(struct rbtree* tree, struct rbtree* z)
{
    struct rbtree* y;
    while (z->parent->color == '0') {
        if (z->parent == z->parent->parent->left) {
            y = z->parent->parent->right;
            if (y->color == '0') {
                z->parent->color = '1';
                y->color = '1';
                z->parent->parent->color = '0';
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) {
                    z = z->parent;
                    LeftRotate(z);
                }
                z->parent->color = '1';
                z->parent->parent->color = '0';
                RightRotate(z->parent->parent);
            }
        } else {
            y = z->parent->parent->left;
            if (y->color == '0') {
                z->parent->color = '1';
                y->color = '1';
                z->parent->parent->color = '0';
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {
                    z = z->parent;
                    RightRotate(z);
                }
                z->parent->color = '1';
                z->parent->parent->color = '0';
                LeftRotate(z->parent->parent);
            }
        }
    }
    while (z->parent != NULL) {
        z = z->parent;
    }
    z->color = '1';
}

struct rbtree* rbtree_min(struct rbtree* tree)
{
    if (!tree) {
        return NULL;
    }
    while (tree->left != NULL) {
        tree = tree->left;
    }
    return tree;
}

struct rbtree* rbtree_max(struct rbtree* tree)
{
    if (!tree) {
        return NULL;
    }
    while (tree->right != NULL) {
        tree = tree->right;
    }
    return tree;
}

struct rbtree* rbtree_lookup(struct rbtree* tree, int key)
{
    while (tree != NULL) {
        if (key == tree->key) {
            return tree;
        } else if (key < tree->key) {
            tree = tree->left;
        } else {
            tree = tree->right;
        }
    }
    return tree;
}

struct rbtree* rbtree_delete(struct rbtree* tree, int key)
{
}