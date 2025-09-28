#include "../include/info_protection.hpp"

long long
diffie_hellman_key_exchange(long long p, long long g, struct keys* key)
{
    if (g >= p)
        return -1;
    long long Ya = mod_pow(g, key->a, p);
    long long Yb = mod_pow(g, key->b, p);

    key->a = mod_pow(Yb, key->a, p);
    key->b = mod_pow(Ya, key->b, p);

    if (key->a == key->b)
        return 0;

    return -1;
}