#include "my_list.h"

using namespace std;

int main()
{
    try {
        cout << "Queue\n";
        queue a(0, "hello");
        a.print();
        for (int i = 1; i < 4; ++i) {
            a.add(i, "the");
            a.print();
        }
        for (int i = 0; i < 4; ++i) {
            a.delete_node();
            a.print();
        }
        cout << "Stack\n";
        stack b(0, "Hello");
        b.print();
        for (int i = 1; i < 4; ++i) {
            b.add(i, "the");
            b.print();
        }
        for (int i = 0; i < 4; ++i) {
            b.delete_node();
            b.print();
        }
        cout << "List\n";
        list c(0, "bay");
        c.print();
        for (int i = 1; i < 4; ++i) {
            if (i % 2) {
                c.add_begin(i, "qwe");
                c.print();
            } else {
                c.add_end(i, "axcz");
                c.print();
            }
        }
        for (int i = 0; i < 4; ++i) {
            c.delete_node(i);
            c.print();
        }
    } catch (const char* s) {
        cout << s << "\n";
        return 0;
    }
}