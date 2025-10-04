#include "../include/info_protection.hpp"

void rsa_encrypt_file(
        const std::string& input_file,
        const std::string& output_file,
        const RSA& keys)
{
    std::ifstream fin(input_file, std::ios::binary);
    std::ofstream fout(output_file, std::ios::binary);
    if (!fin.is_open() || !fout.is_open())
        throw std::runtime_error("Ошибка открытия файла");

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

    char tmp;
    while (fin.read(&tmp, sizeof(tmp))) {
        long int val = static_cast<unsigned char>(tmp);

        long int enc = mod_pow(val, e, n);

        fout.write(reinterpret_cast<char*>(&enc), sizeof(enc));
    }
}
