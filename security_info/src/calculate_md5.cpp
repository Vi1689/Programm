#include "../include/info_protection.hpp"

std::string calculate_md5(const std::string& filename)
{
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Не могу открыть файл: " + filename);
    }

    MD5_CTX md5_context;
    MD5_Init(&md5_context);

    char buffer[1024 * 16];

    while (file.read(buffer, sizeof(buffer)) || file.gcount() > 0) {
        MD5_Update(&md5_context, buffer, file.gcount());
    }

    unsigned char md5_hash[MD5_DIGEST_LENGTH];
    MD5_Final(md5_hash, &md5_context);

    std::string s;
    for (const auto i : md5_hash) {
        s += i;
    }

    return s;
}
