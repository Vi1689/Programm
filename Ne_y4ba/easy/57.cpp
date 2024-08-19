// Решена

#include <iostream>
#include <set>
#include <string>
#include <vector>

bool check(int x)
{
    bool flag;

    x ? flag = true : flag = false;

    return flag;
}

int main()
{
    std::string str1;
    std::string str2;
    std::cin >> str1 >> str2;
    long int count = 0;

    int size1 = str1.size(), size2 = str2.size();

    std::set<std::string> st;
    std::set<std::string>::iterator itr;

    for (int i = 0; i < size2 - 1; ++i) {
        std::string ss;
        ss += str2[i];
        ss += str2[i + 1];
        st.insert(ss);
    }

    for (int i = 0; i < size1 - 1; ++i) {
        std::string ss;
        ss += str1[i];
        ss += str1[i + 1];
        itr = st.find(ss);
        count += check(itr != st.end());
    }

    std::cout << count << "\n";

    return 0;
}