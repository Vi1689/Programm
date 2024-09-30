#include <iostream>

int main()
{
    int n;
    int* arr_n = new int[n];

    std::cin >> n;
    for (int i = 0; i < n; ++i) {
        std::cin >> arr_n[i];
    }

    int x;
    int* arr_x = new int[x];

    std::cin >> x;
    for (int i = 0; i < x; ++i) {
        std::cin >> arr_x[i];
    }

    int k;
    int* arr_k = new int[k];

    std::cin >> k;
    for (int i = 0; i < k; ++i) {
        std::cin >> arr_k[i];
    }

    

    delete[] arr_n;
    delete[] arr_x;
    delete[] arr_k;
}