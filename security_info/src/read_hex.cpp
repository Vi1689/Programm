#include "../include/info_protection.hpp"

std::vector<long int> read_hex(const std::string& hex_filename)
{
    std::vector<long int> data;
    std::ifstream hex_file(hex_filename);

    if (!hex_file) {
        throw std::runtime_error("Cannot open file: " + hex_filename);
    }

    std::string line;
    while (std::getline(hex_file, line)) {
        if (!line.empty()) {
            long int value;
            std::stringstream ss;
            ss << std::hex << line;
            ss >> value;
            data.push_back(value);
        }
    }

    return data;
}