#include "../include/info_protection.hpp"

long int gcd_extended(long int a, long int b, long int& x, long int& y)
{
    if (a == 0) {
        x = 0;
        y = 1;
        return b;
    }

    long int x1, y1;
    long int g = gcd_extended(b % a, a, x1, y1);

    x = y1 - (b / a) * x1;
    y = x1;

    return g;
}