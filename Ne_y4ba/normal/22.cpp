// Решена

#include <deque>
#include <iostream>
#include <vector>

int main()
{
    int n, k;
    std::cin >> n >> k;
    std::vector<long int> section(n);

    for (int i = 0; i < n; ++i) {
        std::cin >> section[i];
    }

    std::deque<int> dq;
    for (int i = 0; i < n; ++i) {
        if (!dq.empty() && dq.front() < i - k + 1) {
            dq.pop_front();
        }

        while (!dq.empty() && section[dq.back()] > section[i]) {
            dq.pop_back();
        }

        dq.push_back(i);

        if (i >= k - 1) {
            std::cout << section[dq.front()] << "\n";
        }
    }

    return 0;
}