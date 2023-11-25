#include "kursach.h"

llrbtree* create()
{
    llrbtree* tree = malloc(sizeof(struct Llrbtree));

    tree->root = NULL;

    return tree;
}

llrbtree* insert(llrbtree* tree, int key, char* value)
{
    tree->root = node_insert(tree->root, key, value);
    tree->root->color = false;
    return tree;
}

node* node_insert(node* tree, int key, char* value)
{
    if (!tree) {
        node* n = malloc(sizeof(node));
        n->key = key;
        n->value = value;
        n->color = true;
        n->left = NULL;
        n->right = NULL;
        return n;
    }

    node* n = tree;

    if (n->key > key) {
        n->left = node_insert(n->left, key, value);
    } else if (n->key < key) {
        n->right = node_insert(n->right, key, value);
    } else {
        n->value = value;
    }

    if (!isRed(n->left) && isRed(n->right)) {
        n = leftRotate(n);
    }
    if (isRed(n->left) && isRed(n->left->left)) {
        n = rightRotate(n);
    }
    if (isRed(n->left) && isRed(n->right)) {
        flipColor(n);
    }

    return n;
}

bool isRed(node* n)
{
    return n ? n->color : false;
}

node* leftRotate(node* x)
{
    node* y = x->right;
    x->right = y->left;
    y->left = x;
    y->color = x->color;
    x->color = true;
    return y;
}

node* rightRotate(node* x)
{
    node* y = x->left;
    x->left = y->right;
    y->right = x;
    y->color = x->color;
    x->color = true;
    return y;
}

void flipColor(node* n)
{
    n->color = !n->color;
    n->left->color = !n->left->color;
    n->right->color = !n->right->color;
}

node* search(llrbtree* tree, int key)
{
    node* n = tree->root;

    while (n) {
        if (key > n->key) {
            n = n->right;
        } else if (key < n->key) {
            n = n->left;
        } else {
            return n;
        }
    }

    return NULL;
}

llrbtree* delete(llrbtree* tree, int key)
{
    if (search(tree, key) == NULL) {
        return tree;
    }

    if (isRed(tree->root->left) && !isRed(tree->root->right)) {
        tree->root->color = true;
    }

    tree->root = node_delete(tree->root, key);
    if (tree->root) {
        tree->root->color = false;
    }

    return tree;
}

node* node_delete(node* n, int key)
{
    node* temp;
    if (key < n->key) {
        if (n->left) {
            if (!isRed(n->left) && !isRed(n->left->left)) {
                n = moveRedtoLeft(n);
            }
            n->left = node_delete(n->left, key);
        }
    } else {
        if (isRed(n->left)) {
            n = rightRotate(n);
        }
        if (key == n->key && !n->right) {
            free(n);
            return NULL;
        }
        if (n->right) {
            if (!isRed(n->right) && !isRed(n->right->left)) {
                n = moveRedtoRight(n);
            }
            if (key == n->key) {
                temp = node_Min(n->right);
                n->key = temp->key;
                n->value = temp->value;
                n->right = deleteMin(n->right);
            } else {
                n->right = node_delete(n->right, key);
            }
        }
    }
    return fixup(n);
}

node* node_Min(node* n)
{
    if (!n) {
        return NULL;
    }
    while (n->left) {
        n = n->left;
    }
    return n;
}

node* deleteMin(node* n)
{
    if (!n) {
        return NULL;
    }
    if (!n->left) {
        free(n);
        return NULL;
    }
    if (!isRed(n->left) && !isRed(n->left->left)) {
        n = moveRedtoLeft(n);
    }
    n->left = deleteMin(n->left);
    return fixup(n);
}

node* moveRedtoLeft(node* n)
{
    flipColor(n);
    if (n && n->right && isRed(n->right->left)) {
        n->right = rightRotate(n->right);
        n = leftRotate(n);
        flipColor(n);
    }
    return n;
}

node* moveRedtoRight(node* n)
{
    flipColor(n);
    if (n && n->left && isRed(n->left->left)) {
        n = rightRotate(n);
        flipColor(n);
    }
    return n;
}

node* fixup(node* n)
{
    if (isRed(n->right)) {
        n = leftRotate(n);
    }
    if (isRed(n->left) && isRed(n->left->left)) {
        n = rightRotate(n);
    }
    if (isRed(n->left) && isRed(n->right)) {
        flipColor(n);
    }
    return n;
}

void print(node* tree, int level)
{
    if (tree) {
        print(tree->left, level + 1);
        for (int i = 0; i < level; ++i) {
            printf("\t");
        }
        printf("%d(%d)", tree->key, level);
        tree->color ? printf("(r)\n") : printf("(b)\n");
        print(tree->right, level + 1);
    }
}

void llrbtree_free(llrbtree* tree)
{
    node_free(tree->root);
    free(tree);
}

void node_free(node* tree)
{
    if (tree) {
        node_free(tree->left);
        node_free(tree->right);
        free(tree);
    }
}