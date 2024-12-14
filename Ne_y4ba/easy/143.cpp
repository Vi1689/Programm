// Решена

#include <iostream>
#include <stack>
#include <vector>

int main()
{
    int n;
    std::cin >> n;
    std::stack<int> dead_end;
    std::vector<int> ways;
    std::vector<int> a;
    while (n--) {
        int z;
        std::cin >> z;
        a.push_back(z);
    }

    dead_end.push(a[0]);

    for (size_t i = 1; i < a.size(); ++i) {
        while (!dead_end.empty()) {
            if (a[i] > dead_end.top()) {
                ways.push_back(dead_end.top());
                dead_end.pop();
            } else {
                break;
            }
        }
        dead_end.push(a[i]);
    }

    while (!dead_end.empty()) {
        ways.push_back(dead_end.top());
        dead_end.pop();
    }

#if 0
    for (const auto& i : ways) {
        std::cout << i << " ";
    }
    std::cout << "\n";
#endif

    for (size_t i = 0; i < ways.size() - 1; ++i) {
        if (ways[i] + 1 != ways[i + 1]) {
            std::cout << "NO\n";
            return 0;
        }
    }
    std::cout << "YES\n";
    return 0;
}