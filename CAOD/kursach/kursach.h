#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int key;
    char* value;
    struct Node* left;
    struct Node* right;
    bool color;
    // true - red
    // false - black
} node;

typedef struct Llrbtree {
    node* root;
} llrbtree;

llrbtree* create();

llrbtree* insert(llrbtree* tree, int key, char* value);

node* node_insert(node* tree, int key, char* value);

bool isRed(node* n);

node* rightRotate(node* x);

node* leftRotate(node* x);

void flipColor(node* n);

node* search(llrbtree* tree, int key);

llrbtree* delete(llrbtree* tree, int key);

node* node_delete(node* tree, int key);

node* deleteMin(node* n);

node* node_Min(node* n);

node* moveRedtoLeft(node* n);

node* moveRedtoRight(node* n);

node* fixup(node* n);

void print(node* tree, int level);

void llrbtree_free(llrbtree* tree);

void node_free(node* tree);