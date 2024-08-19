#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

int main()
{
    int n, k;
    std::cin >> n >> k;

    std::vector<int> arr_n(n);

    for (int i = 0; i < n; ++i) {
        std::cin >> arr_n[i];
    }

    std::vector<int> arr_k(k);

    for (int i = 0; i < k; ++i) {
        std::cin >> arr_k[i];
    }

    return 0;
}