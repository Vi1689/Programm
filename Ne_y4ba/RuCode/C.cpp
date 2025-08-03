#include <iostream>

int main()
{
    int n;
    std::cin >> n;
    unsigned long long a = 1ULL << (8 * n - 1);

    printf("%llx\n", a);
    return 0;
}