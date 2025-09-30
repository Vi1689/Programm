#include "../include/info_protection.hpp"

static long int my_pow(long int a, long int x, long int p, long int y)
{
    long int out = 1;
    while (x) {
        a %= p;
        if (x & 1)
            out *= a;
        x >>= 1;
        a *= a;
    }
    return (out * y) % p;
}

long int baby_step_giant_step(long int a, long int y, long int p)
{
    long int m = std::ceil(std::sqrt(p)), k = m;

    std::vector<long int> baby, giga;
    baby.reserve(m);
    giga.reserve(k);

    for (long int i = 0; i < m; ++i) {
        baby.push_back(my_pow(a, i, p, y));
        giga.push_back(mod_pow(a, m * (i + 1), p));
    }

    for (unsigned long int i = 0; i < baby.size(); ++i) {
        for (unsigned long int j = 0; j < giga.size(); ++j) {
            if (baby[j] == giga[i]) {
                if (mod_pow(a, (i + 1) * m - j, p) == y)
                    return ((i + 1) * m - j);
            }
        }
    }

    return -1;
}