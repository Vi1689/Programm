// Решена

#include <iostream>
#include <stack>
#include <string>

int main()
{
    std::string s;
    std::stack<int> st;
    while (std::cin >> s) {
        if (s == "push") {
            int a;
            std::cin >> a;
            st.push(a);
            std::cout << "ok\n";
        }
        if (s == "pop") {
            if (st.empty()) {
                std::cout << "error\n";
            } else {
                std::cout << st.top() << "\n";
                st.pop();
            }
        }
        if (s == "back") {
            if (st.empty()) {
                std::cout << "error\n";
            } else {
                std::cout << st.top() << "\n";
            }
        }
        if (s == "size") {
            std::cout << st.size() << "\n";
        }
        if (s == "clear") {
            size_t size = st.size();
            for (size_t i = 0; i < size; ++i) {
                st.pop();
            }
            std::cout << "ok\n";
        }
        if (s == "exit") {
            std::cout << "bye\n";
            return 0;
        }
    }
}