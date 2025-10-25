#include "../include/info_protection.hpp"

void dsa_signature(
        const std::string& input_file,
        const std::string& output_file,
        const DSAKeys& keys)
{
    std::string hash = calculate_sha256(input_file);

    long int h = 0;
    for (unsigned char c : hash)
        h = (h + c) % keys.q;
    if (h == 0)
        h = 1;

    long int k, r, s;
    long int k_inv;

    do {
        k = generate_random(1, keys.q - 1);
        r = mod_pow(keys.g, k, keys.p) % keys.q;
        if (r == 0)
            continue;

        long int x_tmp, y_tmp;
        if (gcd_extended(k, keys.q, x_tmp, y_tmp) != 1)
            continue;
        k_inv = (x_tmp % keys.q + keys.q) % keys.q;

        s = (k_inv * (h + keys.x * r)) % keys.q;
    } while (s == 0);

    write_hex({r, s}, output_file);
}
