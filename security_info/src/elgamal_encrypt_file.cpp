#include "../include/info_protection.hpp"

void elgamal_encrypt_file(
        const std::string& input_file,
        const std::string& output_file,
        const ElGamalKeys& keys)
{
    std::ifstream fin(input_file, std::ios::binary);
    std::ofstream fout(output_file, std::ios::binary);
    if (!fin.is_open() || !fout.is_open())
        throw std::runtime_error("Ошибка открытия файла");

    auto y = mod_pow(keys.g, keys.x, keys.p);

    char tmp;
    while (fin.read(&tmp, sizeof(tmp))) {
        long int val = static_cast<unsigned char>(tmp);

        long int k = generate_random(2, keys.p - 2);

        long int a = mod_pow(keys.g, k, keys.p);

        long int b = (val * mod_pow(y, k, keys.p)) % keys.p;

        fout.write(reinterpret_cast<char*>(&a), sizeof(a));
        fout.write(reinterpret_cast<char*>(&b), sizeof(b));
    }
}
