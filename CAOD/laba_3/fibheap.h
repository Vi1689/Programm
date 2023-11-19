#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct node {
    int key, degree;
    char* value;
    bool mark;
    struct node* parent;
    struct node* child;
    struct node* left;
    struct node* right;
};

struct fibheap {
    struct node* min;
    int nnodes;
};

struct fibheap* createHeap();
struct fibheap* fibheap_insert(struct fibheap* heap, int key, char* value);
void FibHeapAddNodeToRootList(struct node* node, struct node* h);
struct node* fibheap_min(struct fibheap* heap);
struct fibheap* fibheap_union(struct fibheap* heap1, struct fibheap* heap2);
struct node* FibHeapLinkLists(struct node* heap1, struct node* heap2);
struct node* fibheap_delete_min(struct fibheap* heap);
void FibHeapConsolidate(struct fibheap* heap);
int D(struct fibheap* n);
void fibheapswap(struct node* x, struct node* y);
void fibheaplink(struct fibheap* heap, struct node* y, struct node* x);
void FibHeapRemoveNodeFromRootList(struct node* z, struct node* heap);
void fibheap_decrease_key(struct fibheap* heap, struct node* x, int newkey);
void fibheapCut(struct fibheap* heap, struct node* x, struct node* y);
void fibheapCascadingCut(struct fibheap* heap, struct node* y);
void fibheap_delete(struct fibheap* heap, struct node* key);
void print(struct fibheap* hp);