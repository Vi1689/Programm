#include "../include/info_protection.h"

long int generate_prime(const long int min, const long int max)
{
    while (1) {
        long int candidate = generate_random(min, max);
        if (prime_number(candidate)) {
            return candidate;
        }
    }
}