#include "kursach.h"
#include <sys/time.h>
#include <time.h>

double wtime()
{
    struct timeval t;
    gettimeofday(&t, NULL);
    return (double)t.tv_sec + (double)t.tv_usec * 1E-6;
}

int main()
{
    llrbtree* a = create();

    for (int i = 0; i < 50000; ++i) {
        a = insert(a, i, "a");
    }

    // print(a);
    // printf("\n");
    // a = delete (a, 3);
    // a = delete (a, 2);
    // a = delete (a, 4);
    // a = delete (a, 1);
    // a = insert(a, 100, "asd");
    print(a);
    printf("\n");

    node* n = search(a, 3);
    printf("%d\n", n->key);
    n = llrbtree_min(a);
    printf("%d\n", n->key);
    n = llrbtree_max(a);
    printf("%d\n", n->key);

    llrbtree_free(a);

    return 0;
}