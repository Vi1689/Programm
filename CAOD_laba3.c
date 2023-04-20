#include "binary_heap.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

#define V 10000
#define INT_MAX 10000000

double wtime()
{
    struct timeval t;
    gettimeofday(&t, NULL);
    return (double)t.tv_sec + (double)t.tv_usec * 1E-6;
}

void dekstra(int** g, int src, int* D, int* prev)
{
    struct heap* h = heap_create(V);
    for (int i = 0; i < V; ++i) {
        D[i] = INT_MAX;
        prev[i] = -1;
        heap_insert(h, i, D[i]);
    }
    D[src] = 0;
    heap_increase_key(h, src, D[src]);
    for (int i = 0; i < V - 1; ++i) {
        int v = heap_extract_min(h);
        for (int u = 0; u < V; ++u) {
            if (D[v] + g[v][u] < D[u]) {
                D[u] = D[v] + g[v][u];
                heap_increase_key(h, u, D[u]);
                prev[u] = v;
            }
        }
    }
    heap_free(h);
}

void print(int** g, int* D, int src, int dst, int* prev)
{
    dekstra(g, src, D, prev);
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
    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < V; ++j) {
            if (i != j && (i != 0 || j != 19)) {
                g[i][j] = 1 + rand() % V;
            }
        }
    }
    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < V; ++j) {
            printf("%d ", g[i][j]);
        }
        printf("\n");
    }
    int* D = malloc(sizeof(int) * V);
    int* prev = malloc(sizeof(int) * V);
    int src = 0, dst = 19;
    double t = wtime(); // src - от какой вершины смотрим
    print(g, D, src, dst, prev); // dst - вершина у которой смотрим путь
    t = wtime() - t;
    printf("time = %.6lf\n", t);
    free(D);
    free(prev);
    for (int i = 0; i < V; ++i) {
        free(g[i]);
    }
    free(g);
    */

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
            if (i != j && ((i + 1) % 100 != 0)) {
                g[i][i + 1] = 1; // + rand() % 20;
                g[i + 1][i] = 1; // + rand() % 20;
            }
        }
    }
    for (int i = 0; i < V - 100; ++i) {
        for (int j = 0; j < V; ++j) {
            if (i != j) {
                g[i][i + 100] = 1; // + rand() % 20;
                g[i + 100][i] = 1; // + rand() % 20;
            }
        }
    }

    // int g[V][V] = {{0, 10, INT_MAX, 30, 100}, {10, 0, 50, INT_MAX,
    // INT_MAX},{INT_MAX, 50, 0, 20, 10}, {30, INT_MAX, 20, 0, 60}, {100,
    // INT_MAX, 10, 60,0}};
    int* D = malloc(sizeof(int) * V);
    int* prev = malloc(sizeof(int) * V);
    int src = 0, dst = 9999;
    double t = wtime(); // src - от какой вершины смотрим
    print(g, D, src, dst, prev); // dst - вершина у которой смотрим путь
    t = wtime() - t;
    printf("time = %.6lf\n", t);
    free(D);
    free(prev);
    for (int i = 0; i < V; ++i) {
        free(g[i]);
    }
    free(g);

    return 0;
}