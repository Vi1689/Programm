#include "../include/info_protection.hpp"

void shamir_decrypt_file(
        const std::string& input_file,
        const std::string& output_file,
        const ShamirKeys& keys)
{
    std::ifstream fin(input_file, std::ios::binary);
    std::ofstream fout(output_file, std::ios::binary);
    if (!fin.is_open() || !fout.is_open())
        throw std::runtime_error("Ошибка открытия файла");

    long int x, y;
    gcd_extended(keys.Ca, keys.p - 1, x, y);
    auto Da = (x % (keys.p - 1) + (keys.p - 1)) % (keys.p - 1);

    gcd_extended(keys.Cb, keys.p - 1, x, y);
    auto Db = (x % (keys.p - 1) + (keys.p - 1)) % (keys.p - 1);

    long int tmp;
    while (fin.read(reinterpret_cast<char*>(&tmp), sizeof(tmp))) {
        // Первый шаг расшифровки (Da)
        long int x3 = mod_pow(tmp, Da, keys.p);

        // Второй шаг расшифровки (Db)
        long int x4 = mod_pow(x3, Db, keys.p);

        char out_char = static_cast<char>(x4);
        fout.write(&out_char, sizeof(out_char));
    }
}
