// Решена

#include <iostream>
#include <vector>

int main()
{
    long int a;
    std::vector<long int> arr;
    while (std::cin >> a) {
        arr.push_back(a);
    }

    for (size_t i = 0; i < arr.size() - 1; ++i) {
        if (arr[i] >= arr[i + 1]) {
            std::cout << "NO\n";
            return 0;
        }
    }
    std::cout << "YES\n";
    return 0;
}