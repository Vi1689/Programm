// Решена

#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>

struct node {
    bool pos;
    std::vector<size_t> arr;
};

std::vector<size_t> dfs(std::vector<node>& graf, size_t src)
{
    std::stack<size_t> st;
    st.push(src);

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

    std::vector<size_t> answer;

    std::vector<std::vector<size_t>> temp;

    for (size_t i = 0; i < n; ++i) {
        if (!graf[i].pos) {
            answer = dfs(graf, i);
            temp.push_back(answer);
        }
    }

    const size_t size = temp.size();

    std::cout << size << "\n";

    for (const auto& i : temp) {
        std::cout << i.size() << "\n";
        for (const auto& j : i) {
            std::cout << (j + 1) << " ";
        }
        std::cout << "\n";
    }

    return 0;
}