// Решена

#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>

struct node {
    bool pos;
    std::vector<size_t> arr;
};

std::vector<size_t> dfs(std::vector<node>& graf)
{
    std::stack<size_t> st;
    st.push(0);

    std::vector<size_t> subsequence;

    while (!st.empty()) {
        size_t temp = st.top();
        st.pop();
        if (!graf[temp].pos) {
            for (size_t j = 0; j < graf[temp].arr.size(); ++j) {
                st.push(graf[temp].arr[j]);
            }
            subsequence.push_back(temp);
        }
        graf[temp].pos = true;
    }
    return subsequence;
}

int main()
{
    size_t n, m;
    std::cin >> n >> m;

    std::vector<node> graf(n);

    for (size_t i = 0; i < m; ++i) {
        size_t a, b;
        std::cin >> a >> b;
        graf[--a].arr.push_back(--b);
        graf[b].arr.push_back(a);
        graf[a].pos = false;
        graf[b].pos = false;
    }

    std::vector<size_t> answer = dfs(graf);

    std::sort(answer.begin(), answer.end());

    std::cout << answer.size() << "\n";

    for (const auto& i : answer) {
        std::cout << (i + 1) << " ";
    }
    std::cout << "\n";

    return 0;
}