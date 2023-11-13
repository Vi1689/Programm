#include "fibheap.h"

struct fibheap* fibheap_insert(struct fibheap* heap, int key, char* value)
{
    struct fibheap* node = malloc(sizeof(*node));
    node->key = key;
    node->value = value;
    node->degree = 0;
    node->mark = false;
    node->parent = NULL;
    node->child = NULL;
    node->left = node;
    node->right = node;
    node->nnodes = heap->nnodes + 1;
    node->min = heap;
    /* Добавляем узел в список корней heap */
    FibHeapAddNodeToRootList(node, heap->min);
    if (heap->min == NULL || node->key < heap->min->key) {
        heap->min = node;
    }
    heap->nnodes = heap->nnodes + 1;
    return heap;
}

void FibHeapAddNodeToRootList(struct fibheap* node, struct fibheap* h)
{
    if (h == NULL) {
        return NULL;
    }
    if (h->left == h) { /* Случай 1: список h содержит один корень */
        h->left = node;
        h->right = node;
        node->right = h;
        node->left = h;
    } else { /* Случай 2: список h содержит более одного корня */
        struct fibheap* lnode = h->left;
        h->left = node;
        node->right = h;
        node->left = lnode;
        lnode->right = node;
    }
}

struct fibheap* fibheap_min(struct fibheap* heap)
{
    return heap->min;
}
struct fibheap* fibheap_union(struct fibheap* heap1, struct fibheap* heap2)
{
    struct fibheap* heap = malloc(sizeof(*heap));
    heap->min = heap1->min;
    FibHeapLinkLists(heap1->min, heap2->min);
    if ((heap1->min == NULL)
        || (heap2->min != NULL && heap2->min->key < heap->min->key)) {
        heap->min = heap2->min;
    }
    heap->nnodes = heap1->nnodes + heap2->nnodes;
    free(heap1);
    free(heap2);
    return heap;
}

struct fibheap* FibHeapLinkLists(struct fibheap* heap1, struct fibheap* heap2)
{
    struct fibheap* left1;
    struct fibheap* left2;
    if (heap1 == NULL || heap2 == NULL) {
        return NULL;
    }
    left1 = heap1->left;
    left2 = heap2->left;
    left1->right = heap2;
    heap2->left = left1;
    heap1->left = left2;
    left2->right = heap1;
    return heap1;
}

struct fibheap* fibheap_delete_min(struct fibheap* heap)
{
    struct fibheap* z = heap->min;
    if (z == NULL) {
        return NULL;
    }
    for (struct fibheap* x; x != NULL; x = z->child) {
        FibHeapAddNodeToRootList(x, heap);
        x->parent = NULL;
    }
    FibHeapRemoveNodeFromRootList(z, heap);
    if (z == z->right) {
        heap->min = NULL;
    } else {
        heap->min = z->right;
        FibHeapConsolidate(heap);
    }
    heap->nnodes = heap->nnodes - 1;
    return z;
}

void FibHeapRemoveNodeFromRootList(struct fibheap* z, struct fibheap* heap){
    
}

struct fibheap*
fibheap_decrease_key(struct fibheap* heap, struct fibheap* node, int newkey);
struct fibheap* fibheap_delete(struct fibheap* heap, int key)
{
    fibheap_decrease_key(heap, key, ~(~0U >> 1));
    fibheap_delete_min(heap);
}