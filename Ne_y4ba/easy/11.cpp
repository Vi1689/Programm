// Решена

#include <iostream>
#include <string>
#include <unordered_map>

int main()
{
    size_t n;
    std::cin >> n;
    std::unordered_map<std::string, std::string> mp1, mp2;
    while (n--) {
        std::string s, s1;
        std::cin >> s >> s1;
        mp1[s] = s1;
        mp2[s1] = s;
    }
    std::string ss;
    std::cin >> ss;
    if (auto a = mp1.find(ss); a != mp1.end()) {
        std::cout << a->second << "\n";
        return 0;
    }
    if (auto a = mp2.find(ss); a != mp2.end()) {
        std::cout << a->second << "\n";
        return 0;
    }
}