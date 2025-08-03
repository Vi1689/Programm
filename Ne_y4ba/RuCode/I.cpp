#include <iostream>

int main()
{
    size_t n;
    std::cin >> n;

    size_t* arr = new size_t[n];

    size_t a = 0, b = 0; // a - нечётное, b - чётное

    for (size_t i = 0; i < n; ++i) {
        std::cin >> arr[i];
        a += (arr[i] & 1);
        b += (!(arr[i] & 1));
    }

    size_t count = 0;

    if (a > b) {
        count = b;

        for (size_t i = 0; i < n; ++i) {
            if (!(arr[i] & 1)) {
                arr[i]++;
            }
        }
    } else {
        count = a;
        for (size_t i = 0; i < n; ++i) {
            if (arr[i] == 0) {
                arr[i]++;
                count++;
            } else if (arr[i] & 1) {
                arr[i]++;
            }
        }
    }

    bool flag = true;

    for (size_t i = 0; i < n - 1; ++i) {
        if (arr[i] != arr[i + 1]) {
            std::cout << count << '\n';
            flag = false;
            break;
        }
    }

    if (flag) {
        if (arr[0] == 0) {
            count += 4;
        } else if (n & 1) {
        } else {
            count += 2;
        }
        std::cout << count << '\n';
    }

    delete[] arr;

    return 0;
}