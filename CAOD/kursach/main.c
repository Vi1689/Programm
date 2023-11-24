#include "kursach.h"

int main()
{
    llrbtree* a = create();

    for (int i = 1; i < 10; ++i) {
        a = insert(a, i, "a");
    }
    
    print(a->root, 1);
    printf("\n");
   
    node* n = search(a, 2);
    printf("\n%s\n", n->value);

    llrbtree_free(a);

    return 0;
}