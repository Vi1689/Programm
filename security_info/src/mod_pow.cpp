#include "../include/info_protection.hpp"

long int mod_pow(long int a, long int x, long int p)
{
    long int out = 1;
    while (x) {
        a %= p;
        if (x & 1)
            out *= a;
        x >>= 1;
        a *= a;
    }
    return out % p;
}