#include "../include/info_protection.hpp"

RSA generate_rsa_keys(int min_p, int max_p)
{
    RSA keys;
    keys.p = generate_prime(min_p, max_p);
    keys.q = generate_prime(min_p, max_p);
    while (keys.p == keys.q)
        keys.q = generate_prime(min_p, max_p);

    long int phi = (keys.p - 1) * (keys.q - 1);

    long int e = 65537;
    long int x, y;
    if (e >= phi || gcd_extended(e, phi, x, y) != 1) {
        e = 3;
        while (gcd_extended(e, phi, x, y) != 1) {
            e += 2;
        }
    }

    gcd_extended(e, phi, x, y);
    keys.d = (x % phi + phi) % phi;

    return keys;
}
