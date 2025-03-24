// Решена

#include <iostream>
#include <vector>

int main()
{
    int n;
    std::cin >> n;
    std::vector<int> arr(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> arr[i];
    }

    int k, temp = arr[0];
    std::cin >> k;

    for (auto const& i : arr) {
        if (i == k) {
            temp = i;
            break;
        } else {
            if (abs(k - temp) > abs(k - i)) {
                temp = i;
            }
        }
    }

    std::cout << temp << "\n";

    return 0;
}