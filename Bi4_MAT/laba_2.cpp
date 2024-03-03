#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void iter(double** a, double* b, double* x, int n, double e)
{
    double* nx = new double[n];
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i != j) {
                a[i][j] /= a[i][i];
            }
        }
        b[i] /= a[i][i];
        a[i][i] = 0;
        nx[i] = b[i];
    }
    int h = 0.1 * n * n * log1p(1.0 / e);
    while (h--) {
        for (int i = 0; i < n; ++i) {
            x[i] = b[i];
            for (int j = 0; j < n; ++j) {
                x[i] -= a[i][j] * nx[j];
            }
            nx[i] = x[i];
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
    double* x = new double[n];
    for (int i = 0; i < n; ++i) {
        a[i] = new double[n];
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            Test >> a[i][j];
        }
        Test >> b[i];
    }
    double e = 0.0001;
    iter(a, b, x, n, e);
    for (int i = 0; i < n; ++i) {
        Out << "x" << i + 1 << " = " << x[i] << "\n";
    }
    for (int i = 0; i < n; ++i) {
        delete[] a[i];
    }
    delete[] a;
    delete[] b;
    delete[] x;
    Test.close();
    Out.close();
}