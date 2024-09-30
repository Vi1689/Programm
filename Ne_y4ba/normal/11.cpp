#include <iostream>
#include <stack>
#include <vector>

struct node {
    bool pos;
    std::vector<size_t> arr;
};

std::vector<size_t> dfs(std::vector<node> matrix, size_t src)
{
    std::stack<size_t> st;
    st.push(src);

    std::vector<size_t> subsequence;

    while (!st.empty()) {
        size_t temp = st.top();
        st.pop();
        if (!matrix[temp].pos) {
            for (size_t j = 0; j < matrix[temp].arr.size(); ++j) {
                st.push(matrix[temp].arr[j]);
                if (src == matrix[temp].arr[j] && subsequence.size() > 2) {
                    subsequence.push_back(temp);
                    return subsequence;
                }
            }
            subsequence.push_back(temp);
        }
        matrix[temp].pos = true;
    }
    subsequence.erase(subsequence.begin(), subsequence.end());

    return subsequence;
}

int main()
{
    size_t n;
    std::cin >> n;

    std::vector<node> matrix(n);

    for (size_t i = 0; i < n; ++i) {
        size_t temp;
        for (size_t j = 0; j < n; ++j) {
            std::cin >> temp;
            if (temp) {
                matrix[i].arr.push_back(j);
                matrix[i].pos = false;
            }
        }
    }

    std::vector<size_t> subsequence;

    for (size_t i = 0; i < n; ++i) {
        subsequence = dfs(matrix, i);

        size_t size = subsequence.size();

        if (size > 2) {
            std::cout << "YES\n";
            std::cout << size << "\n";
            for (size_t i = 0; i < size; ++i) {
                std::cout << (subsequence[i] + 1) << " ";
            }
            std::cout << "\n";
            goto end;
        }
    }

    std::cout << "NO\n";

end:
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

4
2 3 4 5

5
0 1 1 1 0
1 0 0 0 1
1 0 0 0 0
1 0 0 0 1
0 1 0 1 0

*/