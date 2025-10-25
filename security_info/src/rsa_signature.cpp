#include "../include/info_protection.hpp"
#include <vector>

void rsa_signature(
        const std::string& input_file,
        const std::string& output_file,
        const RSA& keys)
{
    std::string s = calculate_md5(input_file);

    long int n = keys.p * keys.q;
    long int phi = (keys.p - 1) * (keys.q - 1);
    long int e = 65537;
    long int x, y;
    if (e >= phi || gcd_extended(e, phi, x, y) != 1) {
        e = 3;
        while (gcd_extended(e, phi, x, y) != 1) {
            e += 2;
        }
    }

    std::vector<long int> vt;
    for (const auto i : s) {
        long int val = static_cast<unsigned char>(i);
        long int enc = mod_pow(val, e, n);
        vt.push_back(enc);
    }

    write_hex(vt, output_file);
}