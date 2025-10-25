#include "../include/info_protection.hpp"

DSAKeys generate_dsa_keys(int min_p, int max_p)
{
    DSAKeys keys{};

    keys.q = generate_prime(50, max_p / 4);

    bool found_p = false;
    for (long int b = 2; b < 50 && !found_p; ++b) {
        long int p_candidate = keys.q * b + 1;
        if (p_candidate >= min_p && p_candidate <= max_p
            && prime_number(p_candidate)) {
            keys.p = p_candidate;
            found_p = true;
        }
    }
    if (!found_p)
        throw std::runtime_error("Не удалось сгенерировать p = b*q + 1");

    for (long int h = 2; h < keys.p; ++h) {
        long int g_candidate = mod_pow(h, (keys.p - 1) / keys.q, keys.p);
        if (g_candidate > 1) {
            keys.g = g_candidate;
            break;
        }
    }

    keys.x = generate_random(1, keys.q - 1);

    keys.y = mod_pow(keys.g, keys.x, keys.p);

    return keys;
}
