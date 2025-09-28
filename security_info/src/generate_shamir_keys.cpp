#include "../include/info_protection.hpp"

// ShamirKeys generate_shamir_keys(int bit_length)
// {
//     gmp_randclass rng(gmp_randinit_default);
//     rng.seed(time(nullptr));

//     ShamirKeys keys;

//     // Генерация простого числа p
//     while (true) {
//         keys.p = rng.get_z_bits(bit_length);
//         if (keys.p % 2 == 0)
//             keys.p += 1;
//         if (fermat_primality(keys.p))
//             break;
//     }

//     mpz_class tmp;
//     // Генерация C1, D1
//     while (true) {
//         keys.C1 = rng.get_z_range(keys.p - 2) + 1;
//         if (gcd_extended(keys.C1, keys.p - 1, tmp, tmp) == 1)
//             break;
//     }
//     gcd_extended(keys.C1, keys.p - 1, tmp, keys.D1);
//     if (keys.D1 < 0)
//         keys.D1 += (keys.p - 1);

//     // Генерация C2, D2
//     while (true) {
//         keys.C2 = rng.get_z_range(keys.p - 2) + 1;
//         if (gcd_extended(keys.C2, keys.p - 1, tmp, tmp) == 1)
//             break;
//     }
//     gcd_extended(keys.C2, keys.p - 1, tmp, keys.D2);
//     if (keys.D2 < 0)
//         keys.D2 += (keys.p - 1);

//     return keys;
// }