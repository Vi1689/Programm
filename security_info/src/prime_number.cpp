#include "../include/info_protection.hpp"

bool prime_number(long int p)
{
    for (long int a = 2; a <= p - 2; ++a) {
        if (mod_pow(a, p - 1, p) != 1)
            return false;
    }

    return true;
}
