// Решена

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

int main()
{
    std::vector<int> a(4);

    for (int i = 0; i < 4; ++i) {
        std::cin >> a[i];
    }

    sort(a.begin(), a.end());

    int sum = 0, flag = 0;
    for (int i = 0; i < 4; ++i) {
        sum += a[i];
        if (sum > 4) {
            flag++;
        }
    }

    if (sum == 1 || !sum) {
        flag = 1;
    }

    std::cout << flag << "\n";

    return 0;
}