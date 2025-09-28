#include "../include/info_protection.hpp"

// void shamir_encrypt_file(
//         const std::string& input_file,
//         const std::string& output_file,
//         const ShamirKeys& keys)
// {
//     std::ifstream fin(input_file, std::ios::binary);
//     std::ofstream fout(output_file, std::ios::binary);
//     if (!fin.is_open() || !fout.is_open())
//         throw std::runtime_error("Ошибка открытия файла");

//     size_t block_size = (mpz_sizeinbase(keys.p.get_mpz_t(), 2) - 1) / 8;
//     std::vector<unsigned char> buffer(block_size);

//     while (fin) {
//         fin.read(reinterpret_cast<char*>(buffer.data()), block_size);
//         size_t read_bytes = fin.gcount();
//         if (read_bytes == 0)
//             break;
//         buffer.resize(read_bytes);

//         mpz_class m = block_to_mpz(buffer);

//         // Шаги Алисы и Боба для шифрования
//         mpz_class x1 = mod_pow(m, keys.C1, keys.p);
//         mpz_class x2 = mod_pow(x1, keys.C2, keys.p);

//         // Записываем размер блока и данные
//         std::vector<unsigned char> out_block = mpz_to_block(x2);
//         size_t data_size = out_block.size();
//         fout.write(reinterpret_cast<char*>(&data_size), sizeof(size_t));
//         fout.write(reinterpret_cast<char*>(out_block.data()), data_size);
//     }
// }
