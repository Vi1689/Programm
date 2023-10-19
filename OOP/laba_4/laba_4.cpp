#include <iostream>
#include <time.h>

using namespace std;

template <typename T>

class matrix {
private:
    T** a;
    int m;
    int n;

public:
    matrix()
    {
        n = 0;
        m = 0;
        a = nullptr;
    }

    matrix(int size1, int size2)
    {
        m = size1;
        n = size2;
        a = (T**)new T*[m];
        for (int i = 0; i < m; ++i) {
            a[i] = (T*)new T[n];
            for (int j = 0; j < n; ++j) {
                a[i][j] = 0;
            }
        }
    }

    matrix(const matrix& _a)
    {
        m = _a.m;
        n = _a.n;
        a = (T**)new T*[m];
        for (int i = 0; i < m; ++i) {
            a[i] = (T*)new T[n];
            for (int j = 0; j < n; ++j) {
                a[i][j] = _a.a[i][j];
            }
        }
    }

    T GetM(int i, int j)
    {
        if ((m > 0) && (n > 0)) {
            return a[i][j];
        } else {
            return 0;
        }
    }
    void SetM(int i, int j, T value)
    {
        if ((i < 0) || (i >= m)) {
            return;
        }
        if ((j < 0) || (j >= n)) {
            return;
        }
        a[i][j] = value;
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

    matrix operator=(const matrix& _a)
    {
        if (n > 0) {
            for (int i = 0; i < m; ++i) {
                delete[] a[i];
            }
        }
        if (m > 0) {
            delete[] a;
        }
        m = _a.m;
        n = _a.n;
        a = (T**)new T*[m];
        for (int i = 0; i < m; ++i) {
            a[i] = (T*)new T[n];
            for (int j = 0; j < n; ++j) {
                a[i][j] = _a.a[i][j];
            }
        }
        return *this;
    }

    ~matrix()
    {
        if (n > 0) {
        }
        for (int i = 0; i < m; ++i) {
            delete[] a[i];
        }
        if (m > 0) {
            delete[] a;
        }
    }
};

int main()
{
    srand(time(NULL));
    matrix<int> M(2, 3);
    M.print();
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 3; j++) {
            M.SetM(i, j, i + j);
        }
    }
    M.print();
    matrix<int> M2 = M;
    M2.print();
    matrix<int> M3;
    M3 = M;
    M3.print();
    matrix<int> M4;
    M4 = M3 = M2 = M;
    M4.print();
    return 0;
}