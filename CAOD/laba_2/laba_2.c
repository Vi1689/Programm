#include "trie_tree.h"

int main()
{
    struct trie* a = trie_create();
    a = trie_insert(a, "there", "120");
    a = trie_insert(a, "hello", "10");
    a = trie_insert(a, "homiak", "1000");
    a = trie_insert(a, "thr", "1234");
    a = trie_insert(a, "help", "12345");
    trie_print(a, 1);
    a = trie_delete(a, "help");
    trie_print(a, 1);
    char* s = trie_lookup(a, "there");
    printf("%s", s);
    printf("\n");
    return 0;
}