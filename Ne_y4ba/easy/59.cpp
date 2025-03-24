// Решена

#include <iostream>
#include <set>
#include <string>

int main()
{
    std::set<std::string> st;
    std::string s;
    while (std::cin >> s) {
        st.insert(s);
    }

    std::cout << st.size() << "\n";

    return 0;
}