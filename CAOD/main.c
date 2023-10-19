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
    /*
    rbtree_add(root(a), 2, "1");
    rbtree_add(root(a), 3, "1");
    rbtree_add(root(a), 4, "1");
    rbtree_add(root(a), 5, "1");
    rbtree_print_dfs(root(a), 1);
    rbtree_delete(root(a), 1);
    printf("\n");
    rbtree_print_dfs(root(a), 1);
    */
    
    for (int i = 2; i < 50001; ++i) {
        if (!(i % (10000 / 2))) {
            double t = wtime();
            for (int j = 1; j < 1000000; ++j) {
                rbtree_lookup(root(a), i);
            }
            t = wtime() - t;
            printf("n = %d\ntime = %.6lf\n", i, t);
        }
        a = rbtree_add(root(a), i, "1");
    }
    
    /*
     for (int i = 50001; i > 1; --i) {
         if (!(i % (10000 / 2))) {
             double t = wtime();
             for (int j = 1; j < 10000; ++j) {
                 rbtree_lookup(root(a), i);
             }
             t = wtime() - t;
             printf("n = %d\ntime = %.6lf\n", i, t);
         }
         rbtree_add(root(a), i, "1");
     }
     */
    printf("\n");
    rbtree_free(root(a));
}