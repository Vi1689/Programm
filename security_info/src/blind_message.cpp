#include "../include/info_protection.hpp"

long int blind_message(
        long int message,
        long int e,
        long int n,
        long int& blinding_factor,
        long int& unblinding_factor)
{
    long int temp;
    do {
        blinding_factor = generate_random(2, n - 1);
    } while (gcd_extended(blinding_factor, n, unblinding_factor, temp) != 1);

    gcd_extended(blinding_factor, n, unblinding_factor, temp);
    unblinding_factor = (unblinding_factor % n + n) % n;

    // blinded = message * (blinding_factor^e) mod n
    long int blinded = (message * mod_pow(blinding_factor, e, n)) % n;
    return blinded;
}