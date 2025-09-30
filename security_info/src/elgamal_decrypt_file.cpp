#include "../include/info_protection.hpp"

void elgamal_decrypt_file(
        const std::string& input_file,
        const std::string& output_file,
        const ElGamalKeys& keys)
{
    std::ifstream fin(input_file, std::ios::binary);
    std::ofstream fout(output_file, std::ios::binary);
    if (!fin.is_open() || !fout.is_open())
        throw std::runtime_error("Ошибка открытия файла");

    long int a, b;
    while (fin.read(reinterpret_cast<char*>(&a), sizeof(a))
           && fin.read(reinterpret_cast<char*>(&b), sizeof(b))) {
        auto tmp = mod_pow(a, keys.p - 1 - keys.x, keys.p);

        long int val = (b * tmp) % keys.p;

        char out_char = static_cast<char>(val);
        fout.write(&out_char, sizeof(out_char));
    }
}
