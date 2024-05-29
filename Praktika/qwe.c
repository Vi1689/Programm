#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#define size 6
#define size 9

int MinIndex(int* D, bool* pos)
{
    int min = INT_MAX, min_index;
    for (int i = 0; i < size; ++i) {
        if (D[i] <= min && !pos[i]) {
            min = D[i];
            min_index = i;
        }
    }
    return min_index;
}

void Algorithm(int ans[size * size], int* D, bool* pos, int* prev, int src)
{
    for (int i = 0; i < size; ++i) {
        D[i] = INT_MAX;
        pos[i] = false;
        prev[i] = -1;
    }
    D[src] = 0;
    for (int i = 0; i < size - 1; ++i) {
        int min = MinIndex(D, pos);
        pos[min] = true;
        for (int j = 0; j < size; ++j) {
            if (D[min] + ans[min * size + j] < D[j]
                && ans[min * size + j] != INT_MAX) {
                D[j] = D[min] + ans[min * size + j];
                prev[j] = min;
            }
        }
    }
}

void Print(int ans[size * size], int* D, bool* pos, int* prev, int src, int dst)
{
    Algorithm(ans, D, pos, prev, src);
    for (int i = 0; i < size; ++i) {
        printf("Расстояние от вершины %d до вершины %d равно - %d\n",
               src + 1,
               i + 1,
               D[i]);
    }
    printf("\n");
    int i = dst, count = 0;
    while (prev[i] != prev[src]) {
        i = prev[i];
        count++;
    }
    i = dst;
    int j = 1, path[count];
    while (prev[i] != prev[src]) {
        path[count - j++] = i + 1;
        i = prev[i];
    }
    printf("Путь из вершины %d в вершину %d\n%d", src + 1, dst + 1, src + 1);
    for (int i = 0; i < count; ++i) {
        printf(" => %d", path[i]);
    }
    printf("\n");
}

int main(int argc, char* argv[])
{
    int src = 1;
    if (argc >= 2) {
        src = atoi(argv[1]);
    }
    int dst = 6;
    if (argc >= 3) {
        dst = atoi(argv[2]);
    }
    if (src < 1 || src > size) {
        src = 1;
    }
    if (dst < 1 || dst > size) {
        dst = 2;
    }
    /*
    int ans[size * size] = {INT_MAX, 7,  9,       INT_MAX, INT_MAX, 14,      7,
                            INT_MAX, 10, 15,      INT_MAX, INT_MAX, 9,       10,
                            INT_MAX, 11, INT_MAX, 2,       INT_MAX, 15,      11,
                            INT_MAX, 6,  INT_MAX, INT_MAX, INT_MAX, INT_MAX, 6,
                            INT_MAX, 9,  14,      INT_MAX, 2,       INT_MAX, 9,
                            INT_MAX};
*/
    int ans[size * size]
            = {INT_MAX, 16,      INT_MAX, INT_MAX, 9,       34,      INT_MAX,
               INT_MAX, INT_MAX, 16,      INT_MAX, INT_MAX, INT_MAX, INT_MAX,
               INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX,
               INT_MAX, 23,      INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX,
               INT_MAX, INT_MAX, INT_MAX, 27,      INT_MAX, INT_MAX, 23,
               12,      9,       INT_MAX, 23,      27,      INT_MAX, INT_MAX,
               INT_MAX, 7,       INT_MAX, 34,      INT_MAX, INT_MAX, INT_MAX,
               INT_MAX, INT_MAX, 19,      INT_MAX, INT_MAX, INT_MAX, INT_MAX,
               INT_MAX, INT_MAX, INT_MAX, 19,      INT_MAX, 45,      INT_MAX,
               INT_MAX, INT_MAX, INT_MAX, 23,      7,       INT_MAX, 45,
               INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, 12,      INT_MAX,
               INT_MAX, INT_MAX, INT_MAX, INT_MAX};

    int* D = malloc(sizeof(int) * size);
    bool* pos = malloc(sizeof(int) * size);
    int* prev = malloc(sizeof(int) * size);

    Print(ans, D, pos, prev, --src, --dst);

    free(D);
    free(pos);
    free(prev);
    return 0;
}