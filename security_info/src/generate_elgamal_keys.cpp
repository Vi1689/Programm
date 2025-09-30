#include "../include/info_protection.hpp"

ElGamalKeys generate_elgamal_keys(int min_p, int max_p)
{
    ElGamalKeys keys;
    keys.p = generate_prime(min_p, max_p);
    keys.g = generate_random(2, keys.p - 2);
    keys.x = generate_random(2, keys.p - 2);

    return keys;
}