#include "../include/info_protection.hpp"
#include <cstdint>
#include <iostream>
#include <vector>

struct cart {
    uint8_t id;
    uint8_t rank;
    uint8_t mast;
};

int main()
{
    std::vector<struct cart> a;

    ElGamalKeys keys = generate_elgamal_keys();

    auto y = mod_pow(keys.g, keys.x, keys.p);

    std::vector<long int> vt;
    for (const auto i : a) {
        long int val = static_cast<unsigned char>(i);

        long int k = generate_random(2, keys.p - 2);

        long int a = mod_pow(keys.g, k, keys.p);

        long int b = (val * mod_pow(y, k, keys.p)) % keys.p;

        vt.push_back(a);
        vt.push_back(b);
    }
}