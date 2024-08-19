// Решена

#include <iostream>

using namespace std;

int main()
{
    int a, b, n;
    cin >> a >> b >> n;
    if (a > b) {
        cout << "Yes\n";
    } else {
        int temp;
        temp = b / n;
        if (!(b % n)) {
            a > temp ? cout << "Yes\n" : cout << "No\n";
        } else {
            temp++;
            a > temp ? cout << "Yes\n" : cout << "No\n";
        }
    }
}