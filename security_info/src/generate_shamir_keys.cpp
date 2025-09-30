#include "../include/info_protection.hpp"

ShamirKeys generate_shamir_keys(int min_p, int max_p)
{
    ShamirKeys keys;
    long int x, y;

    // Генерируем простое число p
    keys.p = generate_prime(min_p, max_p);

    // Генерация Ca и Da
    while (true) {
        keys.Ca = generate_random(2, keys.p - 2);
        if (gcd_extended(keys.Ca, keys.p - 1, x, y) == 1) {
            keys.Da = (x % (keys.p - 1) + (keys.p - 1)) % (keys.p - 1);
            if ((keys.Ca * keys.Da) % (keys.p - 1) == 1)
                break;
        }
    }

    // Генерация Cb и Db
    while (true) {
        keys.Cb = generate_random(2, keys.p - 2);
        if (gcd_extended(keys.Cb, keys.p - 1, x, y) == 1) {
            keys.Db = (x % (keys.p - 1) + (keys.p - 1)) % (keys.p - 1);
            if ((keys.Cb * keys.Db) % (keys.p - 1) == 1)
                break;
        }
    }

    return keys;
}
