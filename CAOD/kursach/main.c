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

    for (int i = 1; i < 8; ++i) {
        a = insert(a, i, "a");
    }
    print(a);
    printf("\n");
    a = delete (a, 4);
    //a = delete (a, 6);
    //a = delete (a, 4);
    print(a);
    printf("\n");
    node* n = search(a, 1);
    printf("%d\n", n->key);



    for (int i = 1; i <= 50001; ++i) {
        if (!(i % (5000))) {
            double t = wtime();
            for (int j = 0; j < 1000000; ++j) {
                search(a, i);
            }
            t = wtime() - t;
            //printf("%.6lf\n", t);
        }
        a = insert(a, i, "a");
    }
    printf("\n");

    llrbtree_free(a);

    return 0;
}