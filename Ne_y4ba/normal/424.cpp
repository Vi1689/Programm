#include <iostream>
#include <string>
#include <vector>

int main()
{
    std::string s;

    std::cin >> s;

    int size = s.size();

    long int left = 0, rigth = 0;

    for (int i = 0, j = size / 2; i < size / 2; ++i, ++j) {
        left += s[i];
        rigth += s[j];
    }

    if(!(left - rigth)){
        std::cout << s << "\n";
    }

    
}