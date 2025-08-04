// Решена

#include <iostream>
#include <map>
#include <string>

int main()
{
    int t;
    std::cin >> t;

    std::map<std::string, int> mp;

    for (int i = 0; i < t; ++i) {
        std::string s;
        std::cin >> s;
        mp[s] = 0;
    }

    int n;
    std::cin >> n;

    int sum_a = 0, sum_b = 0, sum_a_temp = 0, sum_b_temp = 0;

    for (int i = 0; i < n; ++i) {
        std::string s;
        scanf("%d:%d", &sum_a, &sum_b);

        std::cin >> s;

        mp[s] += sum_a - sum_a_temp + sum_b - sum_b_temp;

        sum_a_temp = sum_a;
        sum_b_temp = sum_b;
    }

    std::map<std::string, int>::iterator itr;

    std::string s;
    int max = -1000000000;

    for (itr = mp.begin(); itr != mp.end(); ++itr) {
        if (itr->second >= max) {
            max = itr->second;
            s = itr->first;
        }
    }

    std::cout << s << " " << max << "\n";
}