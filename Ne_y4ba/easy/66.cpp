//Решена

#include <iostream>

int main()
{
    long int max = -1000000000, max_1 = -1000000000, min = 1000000000,
             min_1 = 1000000000;
    int temp;
    while (std::cin >> temp) {
        if (max < temp) {
            max_1 = max;
            max = temp;
        } else {
            if (max_1 < temp) {
                max_1 = temp;
            }
        }
        if (min > temp) {
            min_1 = min;
            min = temp;
        } else {
            if (min_1 > temp) {
                min_1 = temp;
            }
        }
    }

    max* max_1 > min* min_1 ? std::cout << max_1 << " " << max << "\n"
                            : std::cout << min << " " << min_1 << "\n";

    return 0;
}