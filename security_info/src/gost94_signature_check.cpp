#include "../include/info_protection.hpp"

bool gost94_signature_check(
        const std::string& input_file,
        const std::string& output_file,
        const GOST94Keys& keys)
{
    std::string hash = calculate_sha256(input_file);
    std::vector<long int> sig = read_hex(output_file);

    if (sig.size() != 2)
        return false;

    long int r = sig[0];
    long int s = sig[1];

    if (r <= 0 || r >= keys.q || s <= 0 || s >= keys.q)
        return false;

    long int e = 0;
    for (unsigned char c : hash)
        e = (e + c) % keys.q;
    if (e == 0)
        e = 1;

    long int x_tmp, y_tmp;
    if (gcd_extended(e, keys.q, x_tmp, y_tmp) != 1)
        return false;
    long int v = (x_tmp % keys.q + keys.q) % keys.q;

    long int u1 = (s * v) % keys.q;
    long int u2 = (keys.q - (r * v) % keys.q) % keys.q;

    long int u = (mod_pow(keys.a, u1, keys.p) * mod_pow(keys.y, u2, keys.p))
            % keys.p;
    u %= keys.q;

    return u == r;
}
