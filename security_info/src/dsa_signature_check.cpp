#include "../include/info_protection.hpp"

bool dsa_signature_check(
        const std::string& input_file,
        const std::string& output_file,
        const DSAKeys& keys)
{
    std::string hash = calculate_sha256(input_file);
    std::vector<long int> sig = read_hex(output_file);

    if (sig.size() != 2)
        return false;

    long int r = sig[0];
    long int s = sig[1];

    if (r <= 0 || r >= keys.q || s <= 0 || s >= keys.q)
        return false;

    long int h = 0;
    for (unsigned char c : hash)
        h = (h + c) % keys.q;
    if (h == 0)
        h = 1;

    long int x_tmp, y_tmp;
    if (gcd_extended(s, keys.q, x_tmp, y_tmp) != 1)
        return false;
    long int w = (x_tmp % keys.q + keys.q) % keys.q;

    long int u1 = (h * w) % keys.q;
    long int u2 = (r * w) % keys.q;

    long int v = (mod_pow(keys.g, u1, keys.p) * mod_pow(keys.y, u2, keys.p))
            % keys.p;
    v %= keys.q;

    return v == r;
}
