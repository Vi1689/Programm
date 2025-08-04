#include <iostream>
#include <stack>
#include <vector>

struct node {
    std::vector<bool> pos;
    std::vector<int> size;
};

void bfs(std::vector<int>& matrix, int n, struct node a, int src, int dst)
{
    std::stack<int> st;
    st.push(src);
    a.pos[src] = true;
    a.size[src] = 0;
    while (!st.empty()) {
        if ()
    }
}

int main()
{
    int n, src, dst;
    std::cin >> n;
    std::vector<int> matrix(n * n);
    for (int i = 0; i < n * n; ++i) {
        std::cin >> matrix[i];
    }
    std::cin >> src >> dst;
    struct node a;
    for (int i = 0; i < n; ++i) {
        a.pos.push_back(false);
        a.size.push_back(-1);
    }

    bfs(matrix, n, a, --src, --dst);

    return 0;
}