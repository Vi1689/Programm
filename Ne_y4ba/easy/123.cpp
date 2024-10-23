// Решена

#include <iostream>
#include <set>

int main()
{
    std::set<size_t> st;

    size_t a;

    while (std::cin >> a) {
        if (!a) {
            goto end;
        }
        st.insert(a);
    }
end:

    for (const auto& i : st) {
        std::cout << i << "\n";
    }

    return 0;
}