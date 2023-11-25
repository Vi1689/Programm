#include "kursach.h"

int main()
{
    llrbtree* a = create();

    for (int i = 1; i < 5; ++i) {
        a = insert(a, i, "a");
    }

    print(a->root, 0);
    printf("\n");
    a = delete(a, 3);
    a = delete(a, 2);
    a = delete(a, 4);
    a = delete(a, 1);
    print(a->root, 0);
    printf("\n");
   
    //node* n = search(a, 3);
    //printf("\n%s\n", n->value);

    llrbtree_free(a);

    return 0;
}