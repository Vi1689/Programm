#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define V 6
#define INT_MAX 1000000000

int PriorityQueueExtractMin(int* D, bool* pos)
{
    int min = INT_MAX, min_index;
    for (int i = 0; i < V; ++i) {
        if (D[i] <= min && !pos[i]) {
            min = D[i];
            min_index = i;
        }
    }
    return min_index;
}

void ShortestPathDijkstra(int g[V][V], int src, int* D, bool* pos, int* prev)
{
    for (int i = 0; i < V; ++i) {
        D[i] = INT_MAX;
        pos[i] = false;
        prev[i] = -1;
    }
    D[src] = 0;
    for (int i = 0; i < V - 1; ++i) {
        int u = PriorityQueueExtractMin(D, pos);
        pos[u] = true;
        for (int v = 0; v < V; ++v) {
            if (D[u] + g[u][v] < D[v]) {
                D[v] = D[u] + g[u][v];
                prev[v] = u;
            }
        }
    }
}

void print(int g[V][V], int* D, int src, int* prev, int dst, bool* pos)
{
    ShortestPathDijkstra(g, src, D, pos, prev);
    printf("Расстояние от вершины %d до всех остальных\n", src + 1);
    for (int i = 0; i < V; ++i) {
        printf("%d - %d : %d\n", src + 1, i + 1, D[i]);
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
    printf("Путь из вершины %d в вершину %d\n%d ", src + 1, dst + 1, src + 1);
    for (int i = 0; i < count; ++i) {
        printf("%d ", path[i]);
    }
    printf("\n");
}

int main()
{
    int g[V][V]
            = {{INT_MAX, 7, 9, INT_MAX, INT_MAX, 14},
               {7, INT_MAX, 10, 15, INT_MAX, INT_MAX},
               {9, 10, INT_MAX, 11, INT_MAX, 2},
               {INT_MAX, 15, 11, INT_MAX, 6, INT_MAX},
               {INT_MAX, INT_MAX, INT_MAX, 6, INT_MAX, 9},
               {14, INT_MAX, 2, INT_MAX, 9, INT_MAX}};
    int* D = malloc(sizeof(int) * V);
    bool* pos = malloc(sizeof(bool) * V);
    int* prev = malloc(sizeof(int) * V);
    int src = 2, dst = 5;
    src--;
    dst--; // src - от какой вершины смотрим
    print(g, D, src, prev, dst, pos); // dst - вершина у которой смотрим путь
    free(D);
    free(pos);
    free(prev);
    return 0;
}