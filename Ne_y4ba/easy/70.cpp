#include <cmath>
#include <iostream>
#include <set>

int main()
{
    size_t n;
    std::cin >> n;

    std::set<int> st;
    std::set<int>::iterator itr, itr_2;

    for (size_t i = 0; i < n; ++i) {
        int temp;
        std::cin >> temp;
        st.insert(temp);
    }

    int x;
    std::cin >> x;

    itr = std::lower_bound(st.begin(), st.end(), x);
    if (*itr == x) {
        std::cout << x << "\n";
        goto end;
    }
    itr_2 = itr;
    itr--;

    if (abs(*itr - x) > abs(*itr_2 - x)) {
        std::cout << *itr_2 << "\n";
    } else {
        std::cout << *itr << "\n";
    }
end:
    return 0;
}