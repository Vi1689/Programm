#include "../include/info_protection.hpp"

void elgamal_signature(
        const std::string& input_file,
        const std::string& output_file,
        const ElGamalKeys& keys)
{
    std::string s = calculate_sha256(input_file);

    auto y = mod_pow(keys.g, keys.x, keys.p);

    std::vector<long int> vt;
    for (const auto i : s) {
        long int val = static_cast<unsigned char>(i);

        long int k = generate_random(2, keys.p - 2);

        long int a = mod_pow(keys.g, k, keys.p);

        long int b = (val * mod_pow(y, k, keys.p)) % keys.p;

        vt.push_back(a);
        vt.push_back(b);
    }

    write_hex(vt, output_file);
}