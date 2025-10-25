#include "../include/info_protection.hpp"

bool rsa_signature_check(
        const std::string& input_file,
        const std::string& output_file,
        const RSA& keys)
{
    std::string s = calculate_md5(input_file);
    std::vector<long int> vt = read_hex(output_file);

    long int n = keys.p * keys.q;

    std::string out;
    for (const auto i : vt) {
        long int dec = mod_pow(i, keys.d, n);
        char out_char = static_cast<char>(dec);
        out.push_back(out_char);
    }

    return out == s;
}