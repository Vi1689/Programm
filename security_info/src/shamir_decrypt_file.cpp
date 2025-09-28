#include "../include/info_protection.hpp"

// void shamir_decrypt_file(
//         const std::string& input_file,
//         const std::string& output_file,
//         const ShamirKeys& keys)
// {
//     std::ifstream fin(input_file, std::ios::binary);
//     std::ofstream fout(output_file, std::ios::binary);
//     if (!fin.is_open() || !fout.is_open())
//         throw std::runtime_error("Ошибка открытия файла");

//     size_t block_size = (mpz_sizeinbase(keys.p.get_mpz_t(), 2) - 1) / 8;

//     while (fin) {
//         size_t data_size;
//         fin.read(reinterpret_cast<char*>(&data_size), sizeof(size_t));
//         if (!fin)
//             break;

//         std::vector<unsigned char> buffer(data_size);
//         fin.read(reinterpret_cast<char*>(buffer.data()), data_size);
//         if (!fin)
//             break;

//         mpz_class x2 = block_to_mpz(buffer);

//         // Шаги расшифровки: x3 = x2^D1, m = x3^D2
//         mpz_class x3 = mod_pow(x2, keys.D1, keys.p);
//         mpz_class m = mod_pow(x3, keys.D2, keys.p);

//         std::vector<unsigned char> out_block = mpz_to_block(m);
//         fout.write(reinterpret_cast<char*>(out_block.data()),
//         out_block.size());
//     }
// }
