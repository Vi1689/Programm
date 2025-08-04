// Решена

#include <iostream>
#include <stack>
#include <vector>

struct node {
    int x, y;
    char c;
};

int main()
{
    int n;

    node temp;

    std::vector<node> arr;

    std::cin >> n;

    for (int i = 0; i < n; ++i) {
        char cr;
        for (int j = 0; j < n; ++j) {
            std::cin >> cr;
            temp.x = i;
            temp.y = j;
            temp.c = cr;
            arr.push_back(temp);
        }
    }

    int x, y;

    std::cin >> x >> y;

    unsigned int count = 0;

    std::stack<node> st;

    st.push(arr[(--x) * n + (--y)]);

    while (!st.empty()) {
        node help = st.top();
        st.pop();
        arr[help.x * n + help.y] = {help.x, help.y, '*'};

        if (arr[help.x * n + (help.y + 1)].c != '*') {
            arr[help.x * n + (help.y + 1)].c = '*';
            st.push(arr[help.x * n + (help.y + 1)]);
        }
        if (arr[help.x * n + (help.y - 1)].c != '*') {
            arr[help.x * n + (help.y - 1)].c = '*';
            st.push(arr[help.x * n + (help.y - 1)]);
        }
        if (arr[(help.x + 1) * n + help.y].c != '*') {
            arr[(help.x + 1) * n + help.y].c = '*';
            st.push(arr[(help.x + 1) * n + help.y]);
        }
        if (arr[(help.x - 1) * n + help.y].c != '*') {
            arr[(help.x - 1) * n + help.y].c = '*';
            st.push(arr[(help.x - 1) * n + help.y]);
        }
        count++;
    }

    std::cout << count << "\n";

    return 0;
}