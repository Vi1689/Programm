// Решена

#include <iostream>
#include <string>

int main()
{
    int a;
    std::cin >> a;

    long int count = a * 2;

    for (int i = 0; i < a; ++i) {
        std::string s;
        std::cin >> s;

        for (long int j = s.size() - 1; j >= 0; --j) {
            if (s[j] == '0') {
                count++;
            } else if (s[j] == '9') {
                count--;
                break;
            } else {
                break;
            }
        }
    }

    std::cout << count << '\n';

    return 0;
}