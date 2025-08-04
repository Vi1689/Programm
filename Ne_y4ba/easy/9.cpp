// Решена

#include <iostream>
#include <vector>

struct node {
    char visited = 'w';
    std::vector<int> ribs;
};

bool dfs(std::vector<node>& graph, int src, int prev = -1, char color = 'g')
{
    graph[src].visited = color;
    for (auto& j : graph[src].ribs) {
        if (graph[j].visited == 'w') {
            if (graph[src].visited == 'g') {
                if (dfs(graph, j, src, 'b')) {
                    return true;
                }
            } else {
                if (dfs(graph, j, src)) {
                    return true;
                }
            }
        }
        if (graph[j].visited == graph[src].visited && prev != j) {
            return true;
        }
    }

    return false;
}

int main(void)
{
    int number_students, pairs_students;
    std::cin >> number_students >> pairs_students;

    std::vector<node> graph(number_students);
    for (int i = 0, a, b; i < pairs_students; ++i) {
        std::cin >> a >> b;
        graph[--a].ribs.push_back(--b);
        graph[b].ribs.push_back(a);
    }
    for (int i = 0; i < number_students; ++i) {
        if (graph[i].visited == 'w') {
            if (dfs(graph, i)) {
                std::cout << "NO\n";
                goto END;
            }
        }
    }
    std::cout << "YES\n";
END:
    return 0;
}