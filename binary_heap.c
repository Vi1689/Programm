#include "binary_heap.h"
#include <stdio.h>
#include <stdlib.h>

struct heap* heap_create(int maxsize)
{
    struct heap* h = malloc(sizeof(*h));
    if (h != NULL) {
        h->maxsize = maxsize;
        h->size = 0;
        h->node = malloc(sizeof(*h->node) * (maxsize + 1));
        if (!(h->node)) {
            free(h);
            return NULL;
        }
    }
    return h;
}

void heap_free(struct heap* h)
{
    free(h->node);
    free(h);
}

void heap_swap(struct heapnode* a, struct heapnode* b)
{
    struct heapnode temp = *a;
    *a = *b;
    *b = temp;
}

int heap_insert(struct heap* h, int key, int value)
{
    if (h->size >= h->maxsize) {
        return -1;
    }
    h->size++;
    h->node[h->size].key = key;
    h->node[h->size].value = value;
    for (int i = h->size; i > 1 && h->node[i].value < h->node[i / 2].value;
         i = i / 2) {
        heap_swap(&h->node[i], &h->node[i / 2]);
    }
    return 0;
}

void heap_heapify(struct heap* h, int index)
{
    while (1) {
        int left = 2 * index, right = 2 * index + 1, tec = index;
        if ((left <= h->size) && (h->node[left].value < h->node[tec].value)) {
            tec = left;
        }
        if ((right <= h->size) && (h->node[right].value < h->node[tec].value)) {
            tec = right;
        }
        if (tec == index) {
            break;
        }
        heap_swap(&h->node[index], &h->node[tec]);
        index = tec;
    }
}

int heap_extract_min(struct heap* h)
{
    struct heapnode min_index = h->node[1];
    h->node[1] = h->node[h->size--];
    heap_heapify(h, 1);
    return min_index.key;
}

void heap_increase_key(struct heap* h, int index, int newkey)
{
    for (int i = 0; i <= h->size; ++i) {
        if (h->node[i].key == index) {
            h->node[i].value = newkey;
            while (i && newkey < h->node[i / 2].value) {
                heap_swap(&h->node[i], &h->node[i / 2]);
                i = i / 2;
            }
            break;
        }
    }
}