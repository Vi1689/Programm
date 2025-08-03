#include <iostream>
#include <map>

int main()
{
    int n;
    std::cin >> n;

    std::map<int, int, std::greater<int>> mp;

    for (int i = 0, a; i < n; ++i) {
        std::cin >> a;
        mp[a] = i + 1;
    }

    int k;
    std::cin >> k;

    while (k--) {
        int tmp = 0;
        for (const auto& i : mp) {
            std::cout << "retest " << i.second << '\n';

            std::cin >> tmp;

            if (tmp) {
                std::cout << "done\n";
                break;
            }
        }

        if (!tmp) {
            std::cout << "done\n";
        }
        fflush(stdout);
    }

    return 0;
}