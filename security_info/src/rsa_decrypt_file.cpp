#include "../include/info_protection.hpp"

void rsa_decrypt_file(
        const std::string& input_file,
        const std::string& output_file,
        const RSA& keys)
{
    std::ifstream fin(input_file, std::ios::binary);
    std::ofstream fout(output_file, std::ios::binary);
    if (!fin.is_open() || !fout.is_open())
        throw std::runtime_error("Ошибка открытия файла");

    long int n = keys.p * keys.q;

    long int tmp;
    while (fin.read(reinterpret_cast<char*>(&tmp), sizeof(tmp))) {
        long int dec = mod_pow(tmp, keys.d, n);

        char out_char = static_cast<char>(dec);
        fout.write(&out_char, sizeof(out_char));
    }
}
