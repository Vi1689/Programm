#include "queue_array.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define V 5
#define INT_MAX 1000000000

void bfs(int g[V][V], int v, bool* pos, int* prev)
{
    struct queue* q;
    for (int i = 0; i < V; i++) {
        pos[i] = false;
        prev[i] = -1;
    }
    q = queue_create(V); // Создаём очередь
    pos[v] = true; // Обрабатываем стартовую вершину
    printf("Vertex % d\n", v + 1);
    queue_enqueue(q, v);
    while (queue_size(q) > 0) {
        int i = queue_dequeue(q);
        for (int j = 0; j < V; j++) {
            if (g[i][j] != INT_MAX && !pos[j]) {
                queue_enqueue(q, j);
                pos[j] = true;
                prev[j] = i;
                printf("Vertex % d\n", j + 1);
            }
        }
    }
    queue_free(q);
}

void dfs(int g[V][V], bool* pos, int start, int* prev)
{
    pos[start] = true;
    printf("Vertex % d\n", start + 1);
    for (int i = 0; i < V; ++i) {
        if (!pos[i] && g[start][i] != INT_MAX) {
            prev[i] = start;
            dfs(g, pos, i, prev);
        }
    }
}

int kolvo(int g[V][V], int src, int dst)
{
    int* d = malloc(sizeof(int) * V);
    bool* pos = malloc(sizeof(bool) * V);
    for (int i = 0; i < V; ++i) {
        d[i] = 0;
        pos[i] = false;
    }
    d[src] = 1;
    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < V; ++j) {
            if (g[i][j] != INT_MAX && !pos[j]) {
                d[j] = d[i] + d[j];
            }
        }
        pos[i] = true;
    }
    return d[dst];
}

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

int main()
{
    srand(time(NULL));
    /*
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
    */
    int g[V][V]
            = {{INT_MAX, 10, INT_MAX, 30, 100},
               {10, INT_MAX, 50, INT_MAX, INT_MAX},
               {INT_MAX, 50, INT_MAX, 20, 10},
               {30, INT_MAX, 20, INT_MAX, 60},
               {100, INT_MAX, 10, 60, INT_MAX}};
    int* D = malloc(sizeof(int) * V);
    bool* pos = malloc(sizeof(bool) * V);
    int* prev = malloc(sizeof(int) * V);
    int src = 1, dst = 5, v = 1; // v - от какой вершины делать поиск в глубину и ширину
    src--;
    dst--;
    v--; // src - от какой вершины смотрим
    print(g, D, src, prev, dst, pos); // dst - вершина у которой смотрим путь
    printf("\nКоличество путей из %d в %d : %d\n",
           src + 1,
           dst + 1,
           kolvo(g, src, dst));
    for (int i = 0; i < V; ++i) {
        pos[i] = false;
        prev[i] = -1;
    }
    printf("Обход в глубину\n");
    dfs(g, pos, v, prev);
    printf("\n");
    for(int i = 0; i < V; ++i){
        pos[i] = false;
        prev[i] = -1;
    }
    printf("Обход в ширину\n");
    bfs(g, v, pos, prev);
    printf("\n");
    free(D);
    free(pos);
    free(prev);
    // for (int i = 0; i < V; ++i) {
    //     free(g[i]);
    // }
    // free(g);
    return 0;
}