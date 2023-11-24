#include "fibheap.h"

int main()
{
    struct fibheap* a = createHeap();
    a = fibheap_insert(a, 1, "a");
    a = fibheap_insert(a, 2, "a");
    a = fibheap_insert(a, 3, "a");
    //a = fibheap_insert(a, 20, "a");
    //a = fibheap_insert(a, 4, "a");
    print(a);

    printf("\n");

    struct fibheap* b = createHeap();
    b = fibheap_insert(b, 9, "a");
    b = fibheap_insert(b, 7, "a");
    b = fibheap_insert(b, 10, "a");
    //b = fibheap_insert(b, 0, "a");
    print(b);

    printf("\n");

    struct fibheap* c = fibheap_union(a, b);
    print(c);

    return 0;
}