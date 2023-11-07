#include "oke.h"

using namespace std;

int main()
{
    srand(time(NULL));
    char a[10][10];
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            a[i][j] = '0';
            cout << a[i][j] << " ";
        }
        cout << "\n";
    }
}