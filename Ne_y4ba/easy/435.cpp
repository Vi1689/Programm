#include <iostream>

int summ(int n)
{
    int temp = 0;
    for (int i = 1; i <= n; ++i) {
        temp += !(n % i);
    }

    return temp;
}

int main()
{
    int n;
    std::cin >> n;

    int sum = 1, temp = n;

    if (n & 1) {
        n--;
    }
    for (int i = n; i > 0; i -= 2) {
        int a = summ(i);
        if (sum < a) {
            temp = i;
            sum = a;
        }
    }

    std::cout << temp << "\n" << sum << "\n";
}