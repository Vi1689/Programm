#include "../include/info_protection.hpp"

void gost94_signature(
        const std::string& input_file,
        const std::string& output_file,
        const GOST94Keys& keys)
{
    std::string hash = calculate_sha256(input_file);

    long int e = 0;
    for (unsigned char c : hash)
        e = (e + c) % keys.q;
    if (e == 0)
        e = 1;

    long int k, r, s;

    do {
        k = generate_random(1, keys.q - 1);
        r = mod_pow(keys.a, k, keys.p) % keys.q;
        if (r == 0)
            continue;
        s = (k * e + keys.x * r) % keys.q;
    } while (s == 0);

    write_hex({r, s}, output_file);
}
