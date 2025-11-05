#include "../include/info_protection.h"

long int mod_pow(long int base, long int exp, long int mod)
{
    long int result = 1;
    long int b = base % mod;
    while (exp > 0) {
        if (exp & 1)
            result = (result * b) % mod;
        b = (b * b) % mod;
        exp >>= 1;
    }
    return result;
}
