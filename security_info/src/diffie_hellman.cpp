#include "../include/info_protection.hpp"

long int diffie_hellman_key_exchange(long int p, long int g, struct keys* key)
{
    if (g >= p)
        return -1;
    long int Ya = mod_pow(g, key->a, p);
    long int Yb = mod_pow(g, key->b, p);

    key->a = mod_pow(Yb, key->a, p);
    key->b = mod_pow(Ya, key->b, p);

    if (key->a == key->b)
        return 0;

    return -1;
}