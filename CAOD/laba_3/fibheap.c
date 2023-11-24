#include "fibheap.h"
#include <math.h>

struct fibheap* createHeap()
{
    struct fibheap* heap = malloc(sizeof(struct fibheap));

    heap->min = NULL;
    heap->nnodes = 0;

    return heap;
}

struct fibheap* fibheap_insert(struct fibheap* heap, int key, char* value)
{
    struct node* node = malloc(sizeof(*node));
    node->key = key;
    node->value = value;
    node->degree = 0;
    node->mark = false;
    node->parent = NULL;
    node->child = NULL;
    node->left = node;
    node->right = node;
    /* Добавляем узел в список корней heap */
    FibHeapAddNodeToRootList(node, heap->min);
    if (heap->min == NULL || node->key < heap->min->key) {
        heap->min = node;
    }
    heap->nnodes = heap->nnodes + 1;
    return heap;
}

void FibHeapAddNodeToRootList(struct node* node, struct node* h)
{
    if (h == NULL) {
        return;
    }
    if (h->left == h) { /* Случай 1: список h содержит один корень */
        h->left = node;
        h->right = node;
        node->right = h;
        node->left = h;
    } else { /* Случай 2: список h содержит более одного корня */
        struct node* lnode = h->left;
        h->left = node;
        node->right = h;
        node->left = lnode;
        lnode->right = node;
    }
}

struct node* fibheap_min(struct fibheap* heap)
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

struct node* FibHeapLinkLists(struct node* heap1, struct node* heap2)
{
    struct node* left1;
    struct node* left2;
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

struct node* fibheap_delete_min(struct fibheap* heap)
{
    struct node* z = heap->min;
    if (z == NULL) {
        return NULL;
    }
    for (struct node* x = z->child; x != NULL; x = x->left) {
        FibHeapAddNodeToRootList(x, heap->min);
        x->parent = NULL;
        if (x->left == x) {
            break;
        }
    }
    FibHeapRemoveNodeFromRootList(z, heap->min);
    if (z == z->right) {
        heap->min = NULL;
    } else {
        heap->min = z->right;
        FibHeapConsolidate(heap);
    }
    heap->nnodes = heap->nnodes - 1;
    free(heap->min);
    return z;
}

void FibHeapConsolidate(struct fibheap* heap)
{
    int degree = D(heap);
    struct node** a = malloc(sizeof(*a) * degree);
    for (int i = 0; i < degree; ++i) {
        a[i] = NULL;
    }
    for (struct node* w = heap->min->left; w != heap->min; w = w->right) {
        struct node* x = w;
        int d = x->degree;
        while (a[d] != NULL) {
            struct node* y = a[d];
            if (x->key > y->key) {
                fibheapswap(x, y);
            }
            fibheaplink(heap, y, x);
            a[d] = NULL;
            d++;
        }
        a[d] = x;
    }
    heap->min = NULL;
    for (int i = 0; i < degree; ++i) {
        if (a[i] != NULL) {
            FibHeapAddNodeToRootList(a[i], heap->min);
            if (heap->min == NULL || a[i]->key < heap->min->key) {
                heap->min = a[i];
            }
        }
    }
}

void fibheapswap(struct node* x, struct node* y)
{
    struct node* z = x;
    x->child = y->child;
    x->degree = y->degree;
    x->key = y->key;
    x->left = y->left;
    x->mark = y->mark;
    x->parent = y->parent;
    x->right = y->right;
    x->value = y->value;

    y->child = z->child;
    y->degree = z->degree;
    y->key = z->key;
    y->left = z->left;
    y->mark = z->mark;
    y->parent = z->parent;
    y->right = z->right;
    y->value = z->value;
}

int D(struct fibheap* n)
{
    return floor(log(n->nnodes));
}

void fibheaplink(struct fibheap* heap, struct node* y, struct node* x)
{
    x->degree = x->degree + 1;
    FibHeapRemoveNodeFromRootList(y, heap->min);
    y->parent = x;
    FibHeapAddNodeToRootList(y, x->child);
    y->mark = false;
}

void FibHeapRemoveNodeFromRootList(struct node* z, struct node* heap)
{
    heap->right->left = heap->left;
    heap->left->right = heap->right;
}

void fibheap_decrease_key(struct fibheap* heap, struct node* x, int newkey)
{
    if (newkey > x->key) {
        return;
    }
    x->key = newkey;
    struct node* y = x->parent;
    if (y != NULL && x->key < y->key) {
        fibheapCut(heap, x, y);
        fibheapCascadingCut(heap, y);
    }
    if (x->key < heap->min->key || heap->min == NULL) {
        heap->min = x;
    }
}

void fibheapCut(struct fibheap* heap, struct node* x, struct node* y)
{
    FibHeapRemoveNodeFromRootList(x, y);
    y->degree = y->degree - 1;
    FibHeapAddNodeToRootList(x, heap->min);
    x->parent = NULL;
    x->mark = false;
}

void fibheapCascadingCut(struct fibheap* heap, struct node* y)
{
    if (y->parent == NULL)
        return;
    if (y->mark == false) {
        y->mark = true;
    } else {
        fibheapCut(heap, y, y->parent);
        fibheapCascadingCut(heap, y->parent);
    }
}

void fibheap_delete(struct fibheap* heap, struct node* key)
{
    fibheap_decrease_key(heap, key, ~(~0U >> 1));
    fibheap_delete_min(heap);
}

void print(struct fibheap* heap)
{
    struct node* node = heap->min->left;
    printf("%d ", heap->min->key);
    while (node != heap->min) {
        printf("%d ", node->key);
        if (node->child != NULL) {
            struct node* child = node->child;
            while (child != NULL) {
                printf("%d ", child->key);
                child = child->child;
            }
        }
        node = node->left;
    }
    printf("\n");
}