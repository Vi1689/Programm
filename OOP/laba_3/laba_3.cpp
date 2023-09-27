#include <iostream>
#include <time.h>

using namespace std;

class matrix {
private:
    int** a;
    int m;
    int n;
    int summ;

public:
    matrix()
    {
        n = 0;
        m = 0;
        summ = 0;
        a = NULL;
    }

    matrix(int size)
    {
        n = size;
        m = size;
        summ = 0;
        int** b = new int*[m];
        for (int i = 0; i < m; ++i) {
            b[i] = new int[n];
            for (int j = 0; j < n; ++j) {
                b[i][j] = 0;
                if (i == j) {
                    b[i][j] = 1;
                }
            }
        }
        a = b;
    }

    matrix(int size1, int size2)
    {
        m = size1;
        n = size2;
        summ = 0;
        int** b = new int*[m];
        for (int i = 0; i < m; ++i) {
            b[i] = new int[n];
        }
        a = b;
    }

    void input()
    {
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                cin >> a[i][j];
            }
        }
    }

    void autofill()
    {
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                a[i][j] = rand() % 100;
            }
        }
    }

    void ij()
    {
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                a[i][j] = i * j;
            }
        }
    }

    void print()
    {
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                cout << a[i][j] << " ";
            }
            cout << "\n";
        }
        cout << "\n";
    }

    void summa()
    {
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                summ += a[i][j];
            }
        }
        cout << summ << "\n";
    }

    ~matrix()
    {
        for (int i = 0; i < m; ++i) {
            delete[] a[i];
        }
        delete[] a;
    }
};

int main()
{
    srand(time(NULL));
    // matrix M1();
    matrix M2(3);
    matrix M3(3, 4);
    matrix M4(2, 3);
    M2.print();
    M3.print();
    M4.print();
    M2.ij();
    M2.print();
    M3.autofill();
    M3.print();
    M4.input();
    M4.print();
    M3.summa();
    return 0;
}