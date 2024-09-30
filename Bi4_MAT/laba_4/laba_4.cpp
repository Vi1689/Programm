#include <iostream>
#include <vector>

int main()
{
    std::vector<int> a;
    std::vector<int> b;
    std::vector<int> c(10);
    for (int i = 1; i <= 10; ++i) {
        a.push_back(i);
        b.push_back(i * -1);
        c.push_back(a[i - 1] + b[i - 1]);
    }
    for (int i = 0; i < 10; ++i) {
        std::cout << c[i] << " ";
    }
}
