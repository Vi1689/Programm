// Решена

#include <algorithm>
#include <iostream>
#include <vector>

struct node {
    char visited = 'w';
    std::vector<int> ribs;
};

bool dfs(std::vector<node>& graph, int src, std::vector<int>& way)
{
    graph[src].visited = 'g';
    for (auto& j : graph[src].ribs) {
        if (graph[j].visited == 'w') {
            if (dfs(graph, j, way)) {
                graph[src].visited = 'y';
                way.push_back(src);
                return true;
            }
        }
        if (!j || graph[j].visited == 'y') {
            graph[src].visited = 'y';
            way.push_back(src);
            return true;
        }
    }
    graph[src].visited = 'w';
    return false;
}

int main(void)
{
    int vertices, pairs_edges;
    std::cin >> vertices >> pairs_edges;

    std::vector<node> graph(vertices);
    for (int i = 0, a, b; i < pairs_edges; ++i) {
        std::cin >> a >> b;
        graph[--a].ribs.push_back(--b);
    }
    std::vector<int> way;
    for (int i = 0; i < vertices; ++i) {
        if (graph[i].visited == 'w') {
            dfs(graph, i, way);
        }
    }
    way.push_back(0);
    std::sort(way.begin(), way.end());
    if (way.size() > 1) {
        if (way[0] == way[1]) {
            way.erase(way.begin());
        }
    }
    for (const auto& i : way) {
        std::cout << i + 1 << " ";
    }
    std::cout << "\n";
    return 0;
}