// Решена

#include <iostream>
#include <vector>

int main()
{
    size_t k, n;
    std::cin >> k >> n;

    std::vector<int> arr(k);

    std::vector<int> answer;

    for (size_t i = 0; i < n; ++i) {
        int a, b;
        std::cin >> a >> b;

        for (size_t j = 0; j < k; ++j) {
            if (arr[j] == 0 || arr[j] < a) {
                arr[j] = b;
                answer.push_back(j);
                break;
            }
        }

        if (answer.size() != i + 1) {
            std::cout << 0 << ' ' << i + 1 << '\n';
            return 0;
        }
    }

    for (const auto i : answer) {
        std::cout << i + 1 << ' ';
    }
    std::cout << '\n';
    return 0;
}