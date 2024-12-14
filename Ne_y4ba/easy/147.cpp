// Решена

#include <deque>
#include <iostream>
#include <string>

int main()
{
    std::string s;
    std::deque<int> dq;
    while (std::cin >> s) {
        if (s == "push_front") {
            int a;
            std::cin >> a;
            dq.push_front(a);
            std::cout << "ok\n";
        }
        if (s == "push_back") {
            int a;
            std::cin >> a;
            dq.push_back(a);
            std::cout << "ok\n";
        }
        if (s == "pop_front") {
            if (dq.empty()) {
                std::cout << "error\n";
            } else {
                std::cout << dq.front() << "\n";
                dq.pop_front();
            }
        }
        if (s == "pop_back") {
            if (dq.empty()) {
                std::cout << "error\n";
            } else {
                std::cout << dq.back() << "\n";
                dq.pop_back();
            }
        }
        if (s == "front") {
            if (dq.empty()) {
                std::cout << "error\n";
            } else {
                std::cout << dq.front() << "\n";
            }
        }
        if (s == "back") {
            if (dq.empty()) {
                std::cout << "error\n";
            } else {
                std::cout << dq.back() << "\n";
            }
        }
        if (s == "size") {
            std::cout << dq.size() << "\n";
        }
        if (s == "clear") {
            dq.clear();
            std::cout << "ok\n";
        }
        if (s == "exit") {
            std::cout << "bye\n";
            return 0;
        }
    }
}