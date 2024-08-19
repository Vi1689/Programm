// Решена

#include <iostream>
#include <set>
#include <string>

int main()
{
    int x, y, z, n;
    std::cin >> x >> y >> z >> n;

    std::set<int> st;
    std::set<int>::iterator itr;

    for (int i = 0; i < 5 && n > 0; ++i) {
        int k = n % 10;
        n /= 10;
        st.insert(k);
    }

    int count = 0;

    for (itr = st.begin(); itr != st.end(); ++itr) {
        count += ((*itr != x) && (*itr != y) && (*itr != z));
    }

    std::cout << count << "\n";

    return 0;
}