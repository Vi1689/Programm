#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct fibheap {
    int key, degree, nnodes;
    char* value;
    bool mark;
    struct fibheap* parent;
    struct fibheap* child;
    struct fibheap* left;
    struct fibheap* right;
    struct fibheap* min;
};

struct fibheap* fibheap_insert(struct fibheap* heap, int key, char* value);
void FibHeapAddNodeToRootList(struct fibheap* node, struct fibheap* h);
struct fibheap* fibheap_min(struct fibheap* heap);
struct fibheap* fibheap_union(struct fibheap* heap1, struct fibheap* heap2);
struct fibheap* FibHeapLinkLists(struct fibheap* heap1, struct fibheap* heap2);
struct fibheap* fibheap_delete_min(struct fibheap* heap);
struct fibheap*
fibheap_decrease_key(struct fibheap* heap, struct fibheap* node, int newkey);
struct fibheap* fibheap_delete(struct fibheap* heap, int key);