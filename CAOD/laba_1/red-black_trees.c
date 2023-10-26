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

struct rbtree* rbtree_add(struct rbtree* T, int key, char* value)
{
    struct rbtree* tree = T;
    struct rbtree* node;
    if (!tree) {
        node = rbtree_create(key, value);
        node->color = '1';
        return node;
    }
    struct rbtree* parent;
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
    node = rbtree_Add_Fixup(T, node);
    return node;
}

struct rbtree* LeftRotate(struct rbtree* x, struct rbtree* T)
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
    if (y->parent == NULL) {
        T = y;
    }
    y->left = x;
    x->parent = y;
    return T;
}

struct rbtree* RightRotate(struct rbtree* x, struct rbtree* T)
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
    if (y->parent == NULL) {
        T = y;
    }
    y->right = x;
    x->parent = y;
    return T;
}

struct rbtree* rbtree_Add_Fixup(struct rbtree* T, struct rbtree* z)
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
                        T = LeftRotate(z, T);
                    }
                    z->parent->color = '1';
                    z->parent->parent->color = '0';
                    T = RightRotate(z->parent->parent, T);
                }
            } else {
                if (z == z->parent->right) {
                    z = z->parent;
                    T = LeftRotate(z, T);
                }
                z->parent->color = '1';
                z->parent->parent->color = '0';
                T = RightRotate(z->parent->parent, T);
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
                        T = RightRotate(z, T);
                    }
                    z->parent->color = '1';
                    z->parent->parent->color = '0';
                    T = LeftRotate(z->parent->parent, T);
                }
            } else {
                if (z == z->parent->left) {
                    z = z->parent;
                    T = RightRotate(z, T);
                }
                z->parent->color = '1';
                z->parent->parent->color = '0';
                T = LeftRotate(z->parent->parent, T);
            }
        }
    }
    z = T;
    // z = root(z);
    z->color = '1';
    return z;
}

struct rbtree* rbtree_min(struct rbtree* tree)
{
    struct rbtree* tree1 = tree;
    if (!tree1) {
        return NULL;
    }
    while (tree1->left != NULL) {
        tree1 = tree1->left;
    }
    return tree1;
}

struct rbtree* rbtree_max(struct rbtree* tree)
{
    struct rbtree* tree1 = tree;
    if (!tree1) {
        return NULL;
    }
    while (tree1->right != NULL) {
        tree1 = tree1->right;
    }
    return tree1;
}

struct rbtree* rbtree_lookup(struct rbtree* tree1, int key)
{
    struct rbtree* tree = tree1;
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

struct rbtree* rbtree_delete(struct rbtree* T, int key)
{
    struct rbtree* tree = T;
    struct rbtree* z = rbtree_lookup((tree), key);
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
        T = rbtree_delete_Fixup(T, x, z);
    }
    free(z);
    return T;
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

struct rbtree*
rbtree_delete_Fixup(struct rbtree* tree, struct rbtree* x, struct rbtree* z)
{
    if (x) {
        while (x->parent != NULL && x->color == '1') {  
            if (x == x->parent->left) {
                struct rbtree* w = x->parent->right;
                if (w->color == '0') {
                    w->color = '1';
                    x->parent->color = '0';
                    tree = LeftRotate(x->parent, tree);
                    w = x->parent->right;
                }
                if (w->left->color == '1' && w->right->color == '1') {
                    w->color = '0';
                    x = x->parent;
                } else {
                    if (w->right->color == '1') {
                        w->left->color = '1';
                        w->color = '0';
                        tree = RightRotate(w, tree);
                        w = x->parent->right;
                    }
                    w->color = x->parent->color;
                    x->parent->color = '1';
                    w->right->color = '1';
                    tree = LeftRotate(x->parent, tree);
                }
            } else {
                struct rbtree* w = x->parent->left;
                if (w->color == '0') {
                    w->color = '1';
                    x->parent->color = '0';
                    tree = RightRotate(x->parent, tree);
                    w = x->parent->left;
                }
                if (w->right->color == '1' && w->left->color == '1') {
                    w->color = '0';
                    x = x->parent;
                } else {
                    if (w->left->color == '1') {
                        w->right->color = '1';
                        w->color = '0';
                        tree = LeftRotate(w, tree);
                        w = x->parent->left;
                    }
                    w->color = x->parent->color;
                    x->parent->color = '1';
                    w->left->color = '1';
                    tree = RightRotate(x->parent, tree);
                }
            }
        }
        x = tree;
        // x = root(x);
        x->color = '1';
        return x;
    } else {
        if (x == z->parent->left) {
            tree = LeftRotate(z->parent, tree);
            z->parent->parent->color = '0';
            if (z->parent->parent->left != NULL) {
                z->parent->parent->left->color = '1';
            }
            if (z->parent->parent->right != NULL) {
                z->parent->parent->right->color = '1';
            }
        } else {
            tree = RightRotate(z->parent, tree);
            z->parent->parent->color = '0';
            if (z->parent->parent->left != NULL) {
                z->parent->parent->left->color = '1';
            }
            if (z->parent->parent->right != NULL) {
                z->parent->parent->right->color = '1';
            }
        }
        x = tree;
        // x = root(z);
        x->color = '1';
        return x;
    }
}

void rbtree_free(struct rbtree* tree)
{
    if (tree) {
        rbtree_free(tree->left);
        rbtree_free(tree->right);
        free(tree);
    }
}

void rbtree_print_dfs(struct rbtree* tree, int level)
{
    struct rbtree* tree1 = tree;
    if (tree) {
        rbtree_print_dfs(tree1->left, level + 1);
        printf("%d(%d)(%c) ", tree1->key, level, tree1->color);
        rbtree_print_dfs(tree1->right, level + 1);
    }
}

/*
struct rbtree* root(struct rbtree* tree)
{
    while (tree->parent != NULL) {
        tree = tree->parent;
    }
    return tree;
}
*/