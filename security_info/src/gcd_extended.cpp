#include "../include/info_protection.hpp"

long long gcd_extended(long int a, long int b, long int x, long int y)
{
    long int g = 0;
    std::vector<long int> u(3), v(3);
    u[0] = a, u[1] = 1, u[2] = 0;
    v[0] = b, v[1] = 0, v[2] = 1;
    if (a < b) {
        std::swap(u, v);
    }

    while (g != 1) {
        long int q = u[0] / v[0], tmp = g;
        g = u[0] % v[0];
        if (g) {
            x = u[1] - q * v[1];
            y = u[2] - q * v[2];
        } else {
            g = tmp;
            break;
        }
        std::swap(u, v);
        v[0] = g;
        v[1] = x;
        v[2] = y;
    }

    return g;
}