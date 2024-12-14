// Решена

#include <iostream>
#include <stack>
#include <string>

int main()
{
    std::string s;
    std::cin >> s;
    std::stack<char> st;
    for (const auto& i : s) {
        if (i == ')') {
            if (st.empty()) {
                std::cout << "no\n";
                return 0;
            }
            char temp = st.top();
            st.pop();
            if (temp != '(') {
                std::cout << "no\n";
                return 0;
            }
        } else if (i == '}') {
            if (st.empty()) {
                std::cout << "no\n";
                return 0;
            }
            char temp = st.top();
            st.pop();
            if (temp != '{') {
                std::cout << "no\n";
                return 0;
            }
        } else if (i == ']') {
            if (st.empty()) {
                std::cout << "no\n";
                return 0;
            }
            char temp = st.top();
            st.pop();
            if (temp != '[') {
                std::cout << "no\n";
                return 0;
            }
        } else {
            st.push(i);
        }
    }
    if (st.empty()) {
        std::cout << "yes\n";
    } else {
        std::cout << "no\n";
    }
    return 0;
}