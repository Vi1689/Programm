#include "../include/info_protection.hpp"

GOST94Keys generate_gost94_keys(int min_p, int max_p)
{
    GOST94Keys keys{};

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

    for (long int g = 2; g < keys.p; ++g) {
        long int a_candidate = mod_pow(g, (keys.p - 1) / keys.q, keys.p);
        if (a_candidate > 1) {
            keys.a = a_candidate;
            break;
        }
    }

    keys.x = generate_random(1, keys.q - 1);

    keys.y = mod_pow(keys.a, keys.x, keys.p);

    return keys;
}
