#include "../include/info_protection.hpp"

void shamir_encrypt_file(
        const std::string& input_file,
        const std::string& output_file,
        const ShamirKeys& keys)
{
    std::ifstream fin(input_file, std::ios::binary);
    std::ofstream fout(output_file, std::ios::binary);
    if (!fin.is_open() || !fout.is_open())
        throw std::runtime_error("Ошибка открытия файла");

    char tmp;
    while (fin.read(&tmp, sizeof(tmp))) {
        long int val = static_cast<unsigned char>(tmp);

        // Первый шаг шифрования (Ca)
        long int x1 = mod_pow(val, keys.Ca, keys.p);

        // Второй шаг шифрования (Cb)
        long int x2 = mod_pow(x1, keys.Cb, keys.p);

        fout.write(reinterpret_cast<char*>(&x2), sizeof(x2));
    }
}
