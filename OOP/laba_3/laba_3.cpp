#include <iostream>
#include <time.h>

using namespace std;

class matrix {
private:
    int** a;
    int mn;
    int m;
    int n;
    int summ;

public:
    matrix()
    {
        mn = 0;
        n = 0;
        m = 0;
        summ = 0;
        a = NULL;
    }

    matrix(int size)
    {
        mn = size;
        n = 0;
        m = 0;
        summ = 0;
        a = create_matrix();
    }

    matrix(int size1, int size2)
    {
        m = size1;
        n = size2;
        mn = 0;
        summ = 0;
        a = create_matrix();
    }

    int** create_matrix()
    {
        if (mn > 0) {
            int** a = new int*[mn];
            for (int i = 0; i < mn; ++i) {
                a[i] = new int[mn];
                for (int j = 0; j < mn; ++j) {
                    a[i][j] = 0;
                    if (i == j) {
                        a[i][j] = 1;
                    }
                }
            }
            return a;
        }
        if (m > 0) {
            int** a = new int*[m];
            for (int i = 0; i < m; ++i) {
                a[i] = new int[n];
            }
            return a;
        }
        return NULL;
    }

    void input()
    {
        if (mn > 0) {
            for (int i = 0; i < mn; ++i) {
                for (int j = 0; j < mn; ++j) {
                    cin >> a[i][j];
                }
            }
        }
        if (m > 0) {
            for (int i = 0; i < m; ++i) {
                for (int j = 0; j < n; ++j) {
                    cin >> a[i][j];
                }
            }
        }
    }

    void autofill()
    {
        if (mn > 0) {
            for (int i = 0; i < mn; ++i) {
                for (int j = 0; j < mn; ++j) {
                    a[i][j] = rand() % 100;
                }
            }
        }
        if (m > 0) {
            for (int i = 0; i < m; ++i) {
                for (int j = 0; j < n; ++j) {
                    a[i][j] = rand() % 100;
                }
            }
        }
    }

    void ij()
    {
        if (mn > 0) {
            for (int i = 0; i < mn; ++i) {
                for (int j = 0; j < mn; ++j) {
                    a[i][j] = i * j;
                }
            }
        }
    }

    void print()
    {
        if (mn > 0) {
            for (int i = 0; i < mn; ++i) {
                for (int j = 0; j < mn; ++j) {
                    cout << a[i][j] << " ";
                }
                cout << "\n";
            }
            cout << "\n";
        }
        if (m > 0) {
            for (int i = 0; i < m; ++i) {
                for (int j = 0; j < n; ++j) {
                    cout << a[i][j] << " ";
                }
                cout << "\n";
            }
            cout << "\n";
        }
    }

    void summa()
    {
        if (mn > 0) {
            for (int i = 0; i < mn; ++i) {
                for (int j = 0; j < mn; ++j) {
                    summ += a[i][j];
                }
            }
            cout << summ << "\n";
        }
        if (m > 0) {
            for (int i = 0; i < m; ++i) {
                for (int j = 0; j < n; ++j) {
                    summ += a[i][j];
                }
            }
            cout << summ << "\n";
        }
    }

    ~matrix()
    {
        if (mn > 0) {
            for (int i = 0; i < mn; ++i) {
                delete[] a[i];
            }
            delete[] a;
        }
        if (m > 0) {
            for (int i = 0; i < m; ++i) {
                delete[] a[i];
            }
            delete[] a;
        }
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