#include "../include/info_protection.h"

char prime_number(long int p)
{
    for (long int a = 2; a <= p - 2; ++a) {
        if (mod_pow(a, p - 1, p) != 1)
            return 0;
    }

    return 1;
}
