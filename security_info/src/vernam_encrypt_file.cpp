#include "../include/info_protection.hpp"

void vernam_encrypt_file(
        const std::string& input_file,
        const std::string& output_file,
        const keys& key)
{
    std::ifstream fin(input_file, std::ios::binary);
    std::ofstream fout(output_file, std::ios::binary);
    if (!fin.is_open() || !fout.is_open())
        throw std::runtime_error("Ошибка открытия файла");

    std::vector<unsigned char> data(
            (std::istreambuf_iterator<char>(fin)),
            std::istreambuf_iterator<char>());

    std::vector<unsigned char> key_bytes
            = generate_vernama_keys(data.size(), key);

    for (size_t i = 0; i < data.size(); ++i)
        data[i] ^= key_bytes[i];

    fout.write(reinterpret_cast<char*>(data.data()), data.size());
}