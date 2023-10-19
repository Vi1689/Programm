#include "my_list.h"

using namespace std;

int main()
{
    cout << "Queue\n";
    queue a(1, "Hello");
    a.add(2, "qwe");
    a.add(3, "qweqwe");
    a.add(4, "qqwesade");
    a.print();
    a.delete_node();
    a.print();
    a.delete_node();
    a.print();
    a.delete_node();
    a.print();
    a.delete_node();
    a.add(3, "qweqwe");
    a.print();
    cout << "Stack\n";
    stack b(1, "Hello");
    b.add(2, "qwe");
    b.add(3, "qweqwe");
    b.add(4, "qqwesade");
    b.print();
    b.delete_node();
    b.print();
    b.delete_node();
    b.print();
    b.delete_node();
    b.print();
    b.delete_node();
    b.add(3, "qweqwe");
    b.print();
    cout << "List\n";
    list c(1, "sad");
    c.add_begin(2, "qwe");
    c.add_end(3, "axcz");
    c.print();
    c.delete_node("sad");
    c.print();
    c.delete_node(2);
    c.print();
    c.delete_node(3);
    c.print();
}