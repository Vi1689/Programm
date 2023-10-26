#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct trie {
    char* value;
    char ch;
    struct trie* child;
    struct trie* sibling;
};

struct trie* trie_create();
struct trie* trie_insert(struct trie* root, char* value, char ch);
char* trie_lookup(struct trie* root, char* value);
struct trie* trie_delete(struct trie* root, char* value);
struct trie* trie_delete_dfs(
        struct trie* root, struct trie* parent, char* value, int* found);
// struct trie* Getchild(struct trie* root, char value);
// void Setchild(struct trie* root, char value, struct trie* child);
void trie_print(struct trie* root, int level);