// Решена

#include <iostream>
#include <map>
#include <string>
#include <vector>

int main()
{
    std::map<std::string, int> mp;
    std::map<std::string, int>::iterator itr;
    int n;
    std::cin >> n;
    for (int i = 0; i < n; ++i) {
        int m;
        std::string str;
        std::cin >> m;
        for (int j = 0; j < m; ++j) {
            std::cin >> str;
            mp[str]++;
        }
    }

    std::vector<std::string> arr;

    for (itr = mp.begin(); itr != mp.end(); ++itr) {
        if (n == itr->second) {
            arr.push_back(itr->first);
        }
    }

    int size = arr.size();

    std::cout << size << "\n";

    for (int i = 0; i < size; ++i) {
        std::cout << arr[i] << "\n";
    }

    size = mp.size();

    std::cout << size << "\n";

    for (itr = mp.begin(); itr != mp.end(); ++itr) {
        std::cout << itr->first << "\n";
    }

    return 0;
}