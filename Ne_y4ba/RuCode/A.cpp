//  Решена

#include <iostream>

int main()
{
    int a, b;
    std::cin >> a >> b;

    double tmp = (a * 1.0) / b;

    int h = tmp * 10;

    std::cout << (h % 10) << '\n';

    return 0;
}