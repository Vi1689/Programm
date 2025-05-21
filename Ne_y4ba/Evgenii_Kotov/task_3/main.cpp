#include <chrono>
#include <iostream>
#include <vector>

int binary_search(const std::vector<int>& a, int key)
{
    int left = 0, mid = 0;
    int right = a.size() - 1;

    while (left <= right && key >= a[left] && key <= a[right]) {
        mid = left + (right - left) / 2;

        if (a[mid] < key)
            left = mid + 1;
        else if (a[mid] > key)
            right = mid - 1;
        else
            return mid;
    }

    return -1;
}

int optimized_binary_search(const std::vector<int>& a, int key)
{
    int left = 0, mid = 0;
    int right = a.size() - 1;

    while (left <= right && key >= a[left] && key <= a[right]) {
        mid = left + (key - a[left]) / (a[right] - a[left]) * (right - left);

        if (a[mid] < key)
            left = mid + 1;
        else if (a[mid] > key)
            right = mid - 1;
        else
            return mid;
    }

    return -1;
}

void test_performance(const std::vector<int>& arr)
{
    std::vector<int> test_values;
    if (!arr.empty()) {
        test_values.push_back(arr.front());
        test_values.push_back(arr[arr.size() / 2]);
        test_values.push_back(arr.back());
    }

    for (const auto val : test_values) {
        std::cout << "The desired value - " << val << "\n";

        auto start = std::chrono::high_resolution_clock::now();
        auto binary_search_index = binary_search(arr, val);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> binary_search_time = end - start;

        start = std::chrono::high_resolution_clock::now();
        auto optimized_binary_search_index = optimized_binary_search(arr, val);
        end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> optimized_binary_search_time
                = end - start;

        std::cout << "Index - " << binary_search_index
                  << ", Time binary_search - " << binary_search_time.count()
                  << "s\n"
                  << "Index - " << optimized_binary_search_index
                  << ", Time optimized_binary_search - "
                  << optimized_binary_search_time.count() << "s\n"
                  << "binary_search / optimized_binary_search - "
                  << binary_search_time.count()
                        / optimized_binary_search_time.count()
                  << "\n";
    }

    std::cout << "\n";
}

int main()
{
    int size = 100000000;
    std::vector<int> a, b;
    a.reserve(size);
    b.reserve(size);
    for (int i = 0; i < size; ++i) {
        a.emplace_back(i + 1);
        b.emplace_back(i + 1);
    }
    b[b.size() - 1] = ((1 << 31) ^ (~0));

    std::cout << "Uniform increase\n";
    test_performance(a);
    std::cout << "The last value is much higher than the previous ones\n";
    test_performance(b);

    return 0;
}