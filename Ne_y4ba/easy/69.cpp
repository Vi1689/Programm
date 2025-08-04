// Решена

#include <iostream>
#include <vector>

int main()
{
    std::vector<int> arr;
    int temp;
    while (std::cin >> temp) {
        arr.push_back(temp);
    }

    unsigned int count = 0, size = arr.size() - 1;

    for (auto i = 1; i < size; ++i) {
        count += (arr[i] > arr[i - 1] && arr[i] > arr[i + 1]);
    }

    std::cout << count << "\n";
    return 0;
}