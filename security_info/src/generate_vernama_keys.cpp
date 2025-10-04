#include "../include/info_protection.hpp"

std::vector<unsigned char> generate_vernama_keys(size_t length, const keys& key)
{
    std::vector<unsigned char> key_bytes(length);
    long int seed = key.a;
    std::mt19937 gen(seed);
    std::uniform_int_distribution<unsigned char> dist(0, 255);

    for (size_t i = 0; i < length; ++i)
        key_bytes[i] = dist(gen);

    return key_bytes;
}