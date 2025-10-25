#include "../include/info_protection.hpp"

bool write_hex(
        const std::vector<long int>& data, const std::string& hex_filename)
{
    std::ofstream hex_file(hex_filename);
    if (!hex_file.is_open())
        throw std::runtime_error("Ошибка открытия файла");

    for (const auto& value : data) {
        hex_file << std::hex << value << '\n';
    }

    return true;
}