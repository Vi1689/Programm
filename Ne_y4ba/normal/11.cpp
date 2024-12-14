// Решена

#include <iostream>
#include <vector>

struct node {
    char visited = 'w';
    std::vector<int> ribs;
};

bool dfs(
        std::vector<node>& graph,
        int src,
        std::vector<int>& way,
        bool* flag,
        int prev = -1)
{
    graph[src].visited = 'g';
    for (const auto& i : graph[src].ribs) {
        if (graph[i].visited == 'w') {
            if (dfs(graph, i, way, flag, src)) {
                if (src == way[0]) {
                    (*flag) = false;
                }
                if (*flag) {
                    way.push_back(src);
                }
                return true;
            }
        }
        if (graph[i].visited == 'g' && prev != i) {
            if (src == i) {
                way.push_back(src);
                return true;
            }
            way.push_back(i);
            way.push_back(src);
            return true;
        }
    }
    graph[src].visited = 'b';

    return false;
}

int main(void)
{
    int size;
    std::cin >> size;

    std::vector<node> graph(size);
    for (int i = 0, value; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            std::cin >> value;
            if (value) {
                graph[i].ribs.push_back(j);
            }
        }
    }
    std::vector<int> way;
    bool flag = true;
    for (int i = 0; i < size; ++i) {
        if (dfs(graph, i, way, &flag)) {
            std::cout << "YES\n" << way.size() << "\n";
            for (const auto& i : way) {
                std::cout << i + 1 << " ";
            }
            std::cout << "\n";
            goto END;
        }
        way.erase(way.begin(), way.end());
    }
    std::cout << "NO\n";
END:
    return 0;
}

/*

6
0 1 0 0 0 0
1 0 1 1 0 0
0 1 0 0 1 0
0 1 0 0 1 0
0 0 1 1 0 1
0 0 0 0 1 0

*/