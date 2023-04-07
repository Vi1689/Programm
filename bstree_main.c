#include "bstree.h"
#include "hashtab.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>

int getrand(int min, int max)
{
    return (double)rand() / (RAND_MAX + 1.0) * (max - min) + min;
}

double wtime()
{
    struct timeval t;
    gettimeofday(&t, NULL);
    return (double)t.tv_sec + (double)t.tv_usec * 1E-6;
}

int search(unsigned int* arr, unsigned int len){
    int count = 0;
    unsigned int* init = malloc(sizeof(unsigned int) * len);
    for(int i = 0; i < len; ++i){
        init[i] = arr[i];
    }
    for(int i = 0; i < len; ++i){
        for(int j = i + 1; j < len; ++j){
            if(init[i] == init[j] && init[i] != 0){
                count++;
                init[j] = 0;
            }
        }
    }
    free(init);
    return count;
}

int main()
{
    /*FILE* a = fopen("words.txt", "r");
    char** words = (char**)malloc(sizeof(char*) * HASHTAB_SIZE);
    for (int i = 0; i < HASHTAB_SIZE; ++i) {
        words[i] = (char*)malloc(sizeof(char) * 64);
    }
    for (int i = 0; (fscanf(a, "%s", words[i]) == 1) && (i < HASHTAB_SIZE); ++i)
        ;
    fclose(a);
    for(int i = 0, z = 1; i < HASHTAB_SIZE; ++i){
        printf("%d : %s\n",z++, words[i]);
    }
    struct bstree* tree = bstree_create(words[0], 0);
    struct listnode* hashtab[HASHTAB_SIZE];
    struct bstree* tree1;
    struct listnode* node;
    hashtab_init(hashtab);
    srand(time(NULL));
    for (int i = 2; i <= HASHTAB_SIZE; ++i) {
        bstree_add(tree, words[i - 1], i - 1);
        hashtab_add(hashtab, words[i - 1], i - 1);
        if (!(i % 10000)) {
            char* w = words[getrand(0, i - 1)];
            // printf("\n%s\n", w);
            double t = wtime();
            printf("\n%f\n", t);
            tree1 = bstree_lookup(tree, w);
            t = wtime() - t;
            printf("\n%f\n", t);
            printf("Btsree n = %d; time = %.6lf\n", i - 1, t);
            t = wtime();
            printf("\n%f\n", t);
            node = hashtab_lookup(hashtab, w);
            t = wtime() - t;
            printf("\n%f\n", t);
            printf("Hashtab n = %d; time = %.6lf\n", i - 1, t);
        }
    }
    for (int i = 0; i < HASHTAB_SIZE; ++i) {
        free(words[i]);
    }
    free(words);
    */
    /*FILE* a = fopen("words.txt", "r");
    FILE* b = fopen("wordss.txt", "r");
    char** words = (char**)malloc(sizeof(char*) * HASHTAB_SIZE);
    for (int i = 0; i < HASHTAB_SIZE; ++i) {
        words[i] = (char*)malloc(sizeof(char) * 64);
    }
    char** wordss = (char**)malloc(sizeof(char*) * HASHTAB_SIZE);
    for (int i = 0; i < HASHTAB_SIZE; ++i) {
        wordss[i] = (char*)malloc(sizeof(char) * 64);
    }
    for (int i = 0; (fscanf(a, "%s", words[i]) == 1) && (i < HASHTAB_SIZE); ++i)
        ;
    for (int i = 0; (fscanf(b, "%s", wordss[i]) == 1) && (i < HASHTAB_SIZE);
         ++i)
        ;
    fclose(a);
    fclose(b);
    struct bstree* tree = bstree_create(words[0], 0);
    struct bstree* treee = bstree_create(wordss[0], 0);
    struct bstree* tree1;
    srand(time(NULL));
    for (int i = 2; i <= HASHTAB_SIZE; ++i) {
        bstree_add(tree, words[i - 1], i - 1);
        bstree_add(treee, wordss[i - 1], i - 1);
        if (!(i % 10000)) {
            double t = wtime();
            printf("\n%f\n", t);
            tree1 = bstree_max(tree);
            t = wtime() - t;
            printf("\n%f\n", t);
            printf("Btsree norm = %d; time = %.6lf\n", i - 1, t);
            t = wtime();
            printf("\n%f\n", t);
            tree1 = bstree_max(treee);
            t = wtime() - t;
            printf("\n%f\n", t);
            printf("Hashtab hard = %d; time = %.6lf\n", i - 1, t);
        }
    }
    for (int i = 0; i < HASHTAB_SIZE; ++i) {
        free(words[i]);
    }
    free(words);
    for (int i = 0; i < HASHTAB_SIZE; ++i) {
        free(wordss[i]);
    }
    free(wordss);
    */
    FILE* a = fopen("words.txt", "r");
    char** words = (char**)malloc(sizeof(char*) * HASHTAB_SIZE);
    for (int i = 0; i < HASHTAB_SIZE; ++i) {
        words[i] = (char*)malloc(sizeof(char) * 64);
    }
    for (int i = 0; (fscanf(a, "%s", words[i]) == 1) && (i < HASHTAB_SIZE); ++i)
        ;
    fclose(a);
    struct listnode* hashtab[HASHTAB_SIZE];
    unsigned int* arr = malloc(sizeof(unsigned int) * HASHTAB_SIZE);
    struct listnode* node;
    hashtab_init(hashtab);
    srand(time(NULL));
    for (int i = 1; i <= HASHTAB_SIZE; ++i) {
        hashtab_add(hashtab, words[i - 1], i - 1, arr, i - 1);
        if (!(i % 10000)) {
            char* w = words[getrand(0, i - 1)];
            double t = wtime();
            printf("\n%f\n", t);
            node = hashtab_lookup(hashtab, w);
            t = wtime() - t;
            printf("\n%f\n", t);
            printf("Hashtab n = %d; time = %.6lf\n", i, t);
            printf("Kollisii : %d\n", search(arr, i));
        }
    }
    for (int i = 0; i < HASHTAB_SIZE; ++i) {
        free(words[i]);
    }
    free(words);
    free(arr);
    return 0;
}