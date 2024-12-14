// Решена

#include <iostream>
#include <stack>
#include <vector>

int main()
{
    int n;
    std::cin >> n;
    std::vector<int> cities;
    std::stack<int> st, answer;
    while (n--) {
        int a;
        std::cin >> a;
        cities.push_back(a);
    }

    st.push(-1);
    for (size_t i = cities.size() - 1; i > 0; --i) {
        answer.push(st.top());
        if (cities[i] < cities[i - 1]) {
            st.push(i);
        } else {
            while (st.top() != -1) {
                auto temp = st.top();
                st.pop();
                if (cities[temp] < cities[i - 1]) {
                    st.push(temp);
                    break;
                }
            }
        }
    }
    std::cout << st.top() << " ";
    while (!answer.empty()) {
        std::cout << answer.top() << " ";
        answer.pop();
    }
    std::cout << "\n";
    return 0;
}