#include "../include/info_protection.hpp"

bool elgamal_signature_check(
        const std::string& input_file,
        const std::string& output_file,
        const ElGamalKeys& keys)
{
    std::string s = calculate_sha256(input_file);
    std::vector<long int> vt = read_hex(output_file);

    std::string out;
    for (int i = 0; i < vt.size(); i += 2) {
        auto tmp = mod_pow(vt[i], keys.p - 1 - keys.x, keys.p);

        long int val = (vt[i + 1] * tmp) % keys.p;

        char out_char = static_cast<char>(val);
        out.push_back(out_char);
    }

    return out == s;
}