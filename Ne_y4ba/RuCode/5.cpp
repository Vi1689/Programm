#include <iostream>
#include <netinet/in.h>
#include <string>

int main()
{
    std::string s;
    std::cin >> s;

    if (s == "encode") {
        int n = 10;

        std::cout << n << '\n' << htonl(n) << '\n';

    } else {
        int k;
        std::cin >> k;
        std::cout << k << '\n';
    }

    return 0;
}