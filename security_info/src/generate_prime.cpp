#include "../include/info_protection.hpp"

long int generate_prime(const long int& min, const long int& max)
{
    while (true) {
        long int candidate = generate_random(min, max);
        if (prime_number(candidate)) {
            return candidate;
        }
    }
}