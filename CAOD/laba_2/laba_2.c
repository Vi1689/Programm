#include "trie_tree.h"

int main()
{
    struct trie* a = trie_create();
    a = trie_insert(a, "hello", '1');
    a = trie_insert(a, "the", '2');
    a = trie_insert(a, "homs", '3');
    printf("%s\n", trie_lookup(a, "the"));
}