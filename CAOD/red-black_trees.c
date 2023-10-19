#include "red-black_trees.h"

struct rbtree* rbtree_create(int key, char* value)
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
        return NULL;
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
            return NULL;
        }
    }
    node = rbtree_create(key, value);
    node->parent = parent;
    if (key < node->parent->key) {
        node->parent->left = node;
    } else {
        node->parent->right = node;
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
    if (x->parent != NULL) {
        if (x == x->parent->left) {
            x->parent->left = y;
        } else {
            x->parent->right = y;
        }
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
    if (x->parent != NULL) {
        if (x == x->parent->left) {
            x->parent->left = y;
        } else {
            x->parent->right = y;
        }
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
            if (y) {
                if (y->color == '0') {
                    z->parent->color = '1';
                    y->color = '1';
                    z->parent->parent->color = '0';
                    z = z->parent->parent;
                    if (z->parent == NULL) {
                        break;
                    }
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
            if (y) {
                if (y->color == '0') {
                    z->parent->color = '1';
                    y->color = '1';
                    z->parent->parent->color = '0';
                    z = z->parent->parent;
                    if (z->parent == NULL) {
                        break;
                    }
                } else {
                    if (z == z->parent->left) {
                        z = z->parent;
                        RightRotate(z);
                    }
                    z->parent->color = '1';
                    z->parent->parent->color = '0';
                    LeftRotate(z->parent->parent);
                }
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
    z = root(z);
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
    struct rbtree* z = rbtree_lookup(root(tree), key);
    struct rbtree* y = z;
    struct rbtree* x;
    char ycolor = y->color;
    if (!(z->left)) {
        x = z->right;
        RBTreeTransplant(tree, z, z->right);
    } else if (!(z->right)) {
        x = z->right;
        RBTreeTransplant(tree, z, z->left);
    } else {
        y = rbtree_min(z->right);
        ycolor = y->color;
        x = y;
        if (y->parent == z) {
            if (x != NULL) {
                x->parent = y;
            }
        } else {
            RBTreeTransplant(tree, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        RBTreeTransplant(tree, z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }
    if (ycolor == '1') {
        rbtree_delete_Fixup(tree, x, z);
    }
    free(z);
}

void RBTreeTransplant(struct rbtree* tree, struct rbtree* u, struct rbtree* v)
{
    if (u->parent != NULL) {
        if (u == u->parent->left) {
            u->parent->left = v;
        } else {
            u->parent->right = v;
        }
    }
    if (v != NULL) {
        v->parent = u->parent;
    }
}

void rbtree_delete_Fixup(
        struct rbtree* tree, struct rbtree* x, struct rbtree* z)
{
    if (x) {
        while (x->parent != NULL && x->color == '1') {
            if (x == x->parent->left) {
                struct rbtree* w = x->parent->right;
                if (w->color == '0') {
                    w->color = '1';
                    x->parent->color = '0';
                    LeftRotate(x->parent);
                    w = x->parent->right;
                }
                if (w->left->color == '1' && w->right->color == '1') {
                    w->color = '0';
                    x = x->parent;
                } else {
                    if (w->right->color == '1') {
                        w->left->color = '1';
                        w->color = '0';
                        RightRotate(w);
                        w = x->parent->right;
                    }
                    w->color = x->parent->color;
                    x->parent->color = '1';
                    w->right->color = '1';
                    LeftRotate(x->parent);
                }
            } else {
                struct rbtree* w = x->parent->left;
                if (w->color == '0') {
                    w->color = '1';
                    x->parent->color = '0';
                    RightRotate(x->parent);
                    w = x->parent->left;
                }
                if (w->right->color == '1' && w->left->color == '1') {
                    w->color = '0';
                    x = x->parent;
                } else {
                    if (w->left->color == '1') {
                        w->right->color = '1';
                        w->color = '0';
                        LeftRotate(w);
                        w = x->parent->left;
                    }
                    w->color = x->parent->color;
                    x->parent->color = '1';
                    w->left->color = '1';
                    RightRotate(x->parent);
                }
            }
        }
        x = root(x);
        x->color = '1';
    } else {
        if (x == z->parent->left) {
            LeftRotate(z->parent);
            z->parent->parent->color = '0';
            if (z->parent->parent->left != NULL) {
                z->parent->parent->left->color = '1';
            }
            if (z->parent->parent->right != NULL) {
                z->parent->parent->right->color = '1';
            }
        } else {
            RightRotate(z->parent);
            z->parent->parent->color = '0';
            if (z->parent->parent->left != NULL) {
                z->parent->parent->left->color = '1';
            }
            if (z->parent->parent->right != NULL) {
                z->parent->parent->right->color = '1';
            }
        }
        x = root(z);
        x->color = '1';
    }
}

void obxod(struct rbtree* tree)
{
    if (tree) {
        obxod(tree->left);
        obxod(tree->right);
    }
}

void rbtree_free(struct rbtree* tree)
{
    if (tree) {
        obxod(tree->left);
        obxod(tree->right);
        free(tree);
    }
}

void rbtree_print_dfs(struct rbtree* tree, int level)
{
    if (tree) {
        rbtree_print_dfs(tree->left, level + 1);
        printf("%d(%d) ", tree->key, level);
        rbtree_print_dfs(tree->right, level + 1);
    }
}

struct rbtree* root(struct rbtree* tree)
{
    while (tree->parent != NULL) {
        tree = tree->parent;
    }
    return tree;
}