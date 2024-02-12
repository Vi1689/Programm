#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void gays(double** a, double* b, int n)
{
    for (int j = 0; j < n; ++j) {
        double max = -1000000;
        unsigned int pos = 0;
        double* temp;
        for (int i = j; i < n; ++i) {
            if (a[i][j] > max) {
                max = a[i][j];
                pos = i;
            }
        }
        temp = a[j];
        a[j] = a[pos];
        a[pos] = temp;
        max = b[j];
        b[j] = b[pos];
        b[pos] = max;
        max = 1 / a[j][j];
        for (int i = j; i < n; ++i) {
            a[j][i] *= max;
        }
        b[j] *= max;
        for (int i = j + 1; i < n; ++i) {
            for (int q = j + 1; q < n; ++q) {
                a[i][q] -= a[i][j] * a[j][q];
            }
            b[i] -= a[i][j] * b[j];
        }
    }
    for (int i = n - 2; i >= 0; --i) {
        for (int j = i + 1; j < n; ++j) {
            b[i] -= a[i][j] * b[j];
        }
    }
}

int main()
{
    string str = "Gauss_Test_1.txt";
    cin >> str[11];
    ifstream Test(str);
    ofstream Out("otvet.txt");
    unsigned int n;
    Test >> n;
    double** a = new double*[n];
    double* b = new double[n];
    for (int i = 0; i < n; ++i) {
        a[i] = new double[n];
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            Test >> a[i][j];
        }
        Test >> b[i];
    }
    gays(a, b, n);
    for (int i = 0; i < n; ++i) {
        Out << "x" << i + 1 << " = " << b[i] << "\n";
    }
    for (int i = 0; i < n; ++i) {
        delete[] a[i];
    }
    delete[] a;
    delete[] b;

    
    Test.close();
    Out.close();
}