#include "red-black_trees.h"
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
    struct rbtree* a = rbtree_create(1, "1");
    for (int i = 2; i < 50000; ++i) {
        // a = rbtree_add(a, i, "a");
    }
    // rbtree_print_dfs((a), 1);
    /*
    a = rbtree_add((a), 2, "1");
    a = rbtree_add((a), 3, "1");
    a = rbtree_add((a), 4, "1");
    a = rbtree_add((a), 5, "1");
    rbtree_print_dfs((a), 1);
    */
    /*
    for (int i = 2; i < 50001; ++i) {
        if (!(i % (5000))) {
            double t = wtime();
            for (int j = 1; j < 1000000; ++j) {
                a = rbtree_add((a), i, "1");
            }
            t = wtime() - t;
            //printf("%.6lf\n", t);
        }
        a = rbtree_add((a), i, "1");
    }
    */

    for (int i = 50001; i > 0; --i) {
        if (!(i % (5000))) {
            double t = wtime();
            for (int j = 1; j < 1000000; ++j) {
                a = rbtree_add((a), i, "1");
            }
            t = wtime() - t;
            printf("%.6lf\n", t);
        }
    }

    printf("\n");
    rbtree_free((a));
}