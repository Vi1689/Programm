// Решена

#include <iostream>
#include <map>

int main()
{
    std::map<std::string, int> mp;

    std::string s;

    while (std::cin >> s) {
        mp[s]++;
        std::cout << (mp[s] - 1) << " ";
    }
    std::cout << "\n";
    return 0;
}