#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define V 10
#define INT_MAX 1000000000

void ShortestPathDijkstra(int** g, int src, int* D, int* pos, int* prev);

void print(int** g, int* D, int src, int* prev, int dst, int* pos)
{
    ShortestPathDijkstra(g, src, D, pos, prev);
    printf("Расстояние от вершины %d до всех остальных\n", src + 1);
    for (int i = 0; i < V; ++i) {
        printf("%d - %d : %d\n", src + 1, i + 1, D[i]);
    }
    /*for (int i = 0, z = 1; i < V; ++i) {
        printf("%d : %d\n", z++, prev[i] + 1);
    }*/
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

int PriorityQueueExtractMin(int* D, int* pos)
{
    int min = INT_MAX, min_index;
    for (int i = 0; i < V; ++i) {
        if (D[i] <= min && pos[i] == -1) {
            min = D[i];
            min_index = i;
        }
    }
    return min_index;
}

void ShortestPathDijkstra(int** g, int src, int* D, int* pos, int* prev)
{
    for (int i = 0; i < V; ++i) {
        D[i] = INT_MAX;
        pos[i] = -1;
        prev[i] = -1;
    }
    D[src] = 0;
    for (int i = 0; i < V - 1; ++i) {
        int u = PriorityQueueExtractMin(D, pos);
        pos[u] = 1;
        for (int v = 0; v < V; ++v) {
            if (D[u] + g[u][v] < D[v]) {
                D[v] = D[u] + g[u][v];
                prev[v] = u;
            }
        }
    }
}

int main()
{
    srand(time(NULL));
    int** g = malloc(sizeof(int*) * V);
    for (int i = 0; i < V; ++i) {
        g[i] = malloc(sizeof(int) * V);
    }
    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < V; ++j) {
            g[i][j] = INT_MAX;
        }
    }
    for (int i = 0; i < V - 1; ++i) {
        for (int j = 0; j < V; ++j) {
            if (i != j) {
                g[i][j] = 1 + rand() % 100;
            }
        }
    }
    int* D = malloc(sizeof(int) * V);
    int* pos = malloc(sizeof(int) * V);
    int* prev = malloc(sizeof(int) * V);
    int src = 0, dst = 9;   // src - от какой вершины смотрим
    print(g, D, src, prev, dst, pos); // dst - вершина у которой смотрим путь
    free(D);
    free(pos);
    free(prev);
    for (int i = 0; i < V; ++i) {
        free(g[i]);
    }
    free(g);
    return 0;
}