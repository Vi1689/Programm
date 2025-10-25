#include "../include/info_protection.hpp"

std::string calculate_sha256(const std::string& filename)
{
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Не могу открыть файл: " + filename);
    }

    SHA256_CTX sha_context;
    SHA256_Init(&sha_context);

    char buffer[1024 * 16];

    while (file.read(buffer, sizeof(buffer)) || file.gcount() > 0) {
        SHA256_Update(&sha_context, buffer, file.gcount());
    }

    unsigned char sha_hash[SHA256_DIGEST_LENGTH];
    SHA256_Final(sha_hash, &sha_context);

    return std::string(reinterpret_cast<char*>(sha_hash), SHA256_DIGEST_LENGTH);
}