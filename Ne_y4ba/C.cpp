#include <algorithm>
#include <cmath>
#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <numeric>
#include <set>
#include <stdbool.h>
#include <string.h>
#include <string>
#include <vector>

using namespace std;

#define pb push_back
#define ll long long
#define vi vector<int>
#define len length
#define ui unsigned int
#define er erase
#define PI 3.14159265
#define INT_MAX (~0U >> 1)

int gcd(unsigned int a, unsigned int b)
{
    while (b != 0) {
        unsigned int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int BP(vector<int> a, int key, int n)
{
    int left = 0, right = n - 1, mid;
    while (left <= right) {
        mid = (right + left) / 2;
        if (key < a[mid]) {
            right = mid - 1;
        } else if (key > a[mid]) {
            left = mid + 1;
        } else {
            return 1;
        }
    }
    return 0;
}

int main()
{
    unsigned int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;

        int** a = new int*[n];

        for (int i = 0; i < n; ++i) {
            a[i] = new int[m];
        }

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                cin >> a[i][j];
            }
        }

        if (n == 1) {
            if (a[0][0] > a[0][1]) {
                a[0][0] = a[0][1];
            }

            for (int i = 1; i < m - 1; ++i) {
                if (a[0][i] > a[0][i - 1] && a[0][i] > a[0][i + 1]) {
                    a[0][i] = a[0][i - 1] * (a[0][i - 1] >= a[0][i + 1])
                            + a[0][i + 1] * (a[0][i + 1] > a[0][i - 1]);
                }
            }

            if (a[0][m - 1] > a[0][m - 2]) {
                a[0][m - 1] = a[0][m - 2];
            }

            for (int i = 0; i < m; ++i) {
                cout << a[0][i] << " ";
            }

            cout << "\n";

            for (int i = 0; i < n; ++i) {
                delete[] a[i];
            }

            delete[] a;

            continue;
        }

        if (a[0][0] > a[1][0] && a[0][0] > a[0][1]) {
            a[0][0] = (a[1][0] >= a[0][1]) * a[1][0]
                    + (a[1][0] < a[0][1]) * a[0][1];
        }

        for (int i = 1; i < m - 1; ++i) {
            if (a[0][i] > a[0][i - 1] && a[0][i] > a[0][i + 1]
                && a[0][i] > a[1][i]) {
                a[0][i] = a[0][i - 1]
                                * (a[0][i - 1] >= a[0][i + 1]
                                   && a[0][i - 1] >= a[1][i])
                        + a[0][i + 1]
                                * (a[0][i + 1] > a[0][i - 1]
                                   && a[0][i + 1] >= a[1][i])
                        + a[1][i]
                                * (a[1][i] > a[0][i + 1]
                                   && a[1][i] > a[0][i - 1]);
            }
        }

        if (a[0][m - 1] > a[0][m - 2] && a[0][m - 1] > a[1][m - 1]) {
            a[0][m - 1] = a[0][m - 2] * (a[0][m - 2] >= a[1][m - 1])
                    + a[1][m - 1] * (a[1][m - 1] > a[0][m - 2]);
        }
        /*
                for (int i = 1; i < n - 1; ++i) {
                    if (a[i][0] > a[i + 1][0] && a[i][0] > a[i - 1][0]
                        && a[i][0] > a[i][1]) {
                        a[i][0] = a[i + 1][0]
                                        * (a[i + 1][0] >= a[i - 1][0]
                                           && a[i + 1][0] >= a[i][1])
                                + a[i - 1][0]
                                        * (a[i - 1][0] > a[i + 1][0]
                                           && a[i - 1][0] >= a[i][1])
                                + a[i][1]
                                        * (a[i][1] > a[i - 1][0]
                                           && a[i][1] > a[i + 1][0]);
                    }
                }
        */
        for (int i = 1; i < n - 1; ++i) {
            for (int j = 0; j < m; ++j) {
                if (j == m - 1) {
                    if (a[i][j] > a[i][j - 1] && a[i][j] > a[i - 1][j]
                        && a[i][j] > a[i + 1][j]) {
                        a[i][j] = a[i][j - 1]
                                        * (a[i][j - 1] >= a[i - 1][j]
                                           && a[i][j - 1] >= a[i + 1][j])
                                + a[i - 1][j]
                                        * (a[i - 1][j] >= a[i + 1][j]
                                           && a[i - 1][j] > a[i][j - 1])
                                + a[i + 1][j]
                                        * (a[i + 1][j] > a[i][j - 1]
                                           && a[i + 1][j] > a[i - 1][j]);
                    }
                } else if (j == 0) {
                    if (a[i][j] > a[i + 1][j] && a[i][j] > a[i - 1][j]
                        && a[i][j] > a[i][j + 1]) {
                        a[i][j] = a[i + 1][j]
                                        * (a[i + 1][j] >= a[i - 1][j]
                                           && a[i + 1][j] >= a[i][j + 1])
                                + a[i - 1][j]
                                        * (a[i - 1][j] > a[i + 1][j]
                                           && a[i - 1][j] >= a[i][j + 1])
                                + a[i][1]
                                        * (a[i][1] > a[i - 1][j]
                                           && a[i][1] > a[i + 1][j + 1]);
                    }
                } else {
                    if (a[i][j] > a[i + 1][j] && a[i][j] > a[i - 1][j]
                        && a[i][j] > a[i][j + 1] && a[i][j] > a[i][j - 1]) {
                        a[i][j] = a[i + 1][j]
                                        * (a[i + 1][j] >= a[i - 1][j]
                                           && a[i + 1][j] >= a[i][j + 1]
                                           && a[i + 1][j] >= a[i][j - 1])
                                + a[i - 1][j]
                                        * (a[i - 1][j] >= a[i][j + 1]
                                           && a[i - 1][j] >= a[i][j - 1]
                                           && a[i - 1][j] > a[i + 1][j])
                                + a[i][j + 1]
                                        * (a[i][j + 1] >= a[i][j - 1]
                                           && a[i][j + 1] > a[i + 1][j]
                                           && a[i][j + 1] > a[i - 1][j])
                                + a[i][j - 1]
                                        * (a[i][j - 1] > a[i][j + 1]
                                           && a[i][j - 1] > a[i + 1][j]
                                           && a[i][j - 1] > a[i - 1][j]);
                    }
                }
            }
        }

        if (a[n - 1][0] > a[n - 2][0] && a[n - 1][0] > a[n - 1][1]) {
            a[n - 1][0] = a[n - 2][0] * (a[n - 2][0] >= a[n - 1][1])
                    + a[n - 1][1] * (a[n - 1][1] > a[n - 2][0]);
        }

        for (int i = 1; i < m - 1; ++i) {
            if (a[n - 1][i] > a[n - 1][i - 1] && a[n - 1][i] > a[n - 1][i + 1]
                && a[n - 1][i] > a[n - 2][i]) {
                a[n - 1][i] = a[n - 1][i - 1]
                                * (a[n - 1][i - 1] >= a[n - 1][i + 1]
                                   && a[n - 1][i - 1] >= a[n - 2][i])
                        + a[n - 1][i + 1]
                                * (a[n - 1][i + 1] > a[n - 1][i - 1]
                                   && a[n - 1][i + 1] >= a[n - 2][i])
                        + a[n - 2][i]
                                * (a[n - 2][i] > a[n - 1][i + 1]
                                   && a[n - 2][i] > a[n - 1][i - 1]);
            }
        }

        if (a[n - 1][m - 1] > a[n - 2][m - 1]
            && a[n - 1][m - 1] > a[n - 1][m - 2]) {
            a[n - 1][m - 1]
                    = a[n - 2][m - 1] * (a[n - 2][m - 1] >= a[n - 1][m - 2])
                    + a[n - 1][m - 2] * (a[n - 1][m - 2] > a[n - 2][m - 1]);
        }

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                cout << a[i][j] << " ";
            }
            cout << "\n";
        }

        for (int i = 0; i < n; ++i) {
            delete[] a[i];
        }

        delete[] a;
    }
}