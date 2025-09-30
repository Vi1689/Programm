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

    long int tmp;
    while (fin.read(reinterpret_cast<char*>(&tmp), sizeof(tmp))) {
        // Первый шаг расшифровки (Da)
        long int x3 = mod_pow(tmp, keys.Da, keys.p);

        // Второй шаг расшифровки (Db)
        long int x4 = mod_pow(x3, keys.Db, keys.p);

        char out_char = static_cast<char>(x4);
        fout.write(&out_char, sizeof(out_char));
    }
}
