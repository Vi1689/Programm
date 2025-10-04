#include "../include/info_protection.hpp"

std::vector<unsigned char> generate_vernama_keys(size_t length, const keys& key)
{
    std::vector<unsigned char> key_bytes(length);
    srand(key.a);
    for (size_t i = 0; i < length; ++i)
        key_bytes[i] = rand() % 256;

    return key_bytes;
}