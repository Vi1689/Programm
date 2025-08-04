// Решена

#include <iostream>
#include <map>

int main()
{
    std::map<std::string, int> mp;

    std::string s;

    while (std::cin >> s) {
        mp[s]++;
    }

    int max = -1000000000;

    for (auto itr = mp.begin(); itr != mp.end(); ++itr) {
        if (max < itr->second) {
            max = itr->second;
            s = itr->first;
        }
    }

    std::cout << s << "\n";
    return 0;
}