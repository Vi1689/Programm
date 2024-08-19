#include <iostream>
#include <string>
#include <vector>

int main()
{
    int n, m;
    std::cin >> n >> m;
    bool flag = true;

    int* a = new int[1000];
    int* b = new int[1000];

    for (int i = 0; i < 1000; ++i) {
        a[i] = 0;
        b[i] = 0;
    }

    for (int i = 0, aa, bb; i < m; ++i) {
        std::cin >> aa >> bb;
        a[--aa]++;
        b[--bb]++;
    }

    for (int i = 0; i < 1000; ++i) {
        if (a[i] > 1 || b[i] > 1) {
            flag = false;
            break;
        }
    }

    if (flag) {
        std::cout << "YES\n";
    } else {
        std::cout << "NO\n";
    }

    delete[] a;
    delete[] b;

    return 0;
}