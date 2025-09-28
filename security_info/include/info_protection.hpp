#pragma once
#include <climits>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <gmpxx.h>
#include <random>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

// ЛР1
long int mod_pow(long int a, long int x, long int p);
bool prime_number(long int p);
long long gcd_extended(long int a, long int b, long int x, long int y);

// ЛР2
long int baby_step_giant_step(long int a, long int y, long int p);

// ЛР3
struct keys {
    long long a, b = 0;
};
long long
diffie_hellman_key_exchange(long long p, long long g, struct keys* key);

// // ЛР4
// struct ShamirKeys {
//     mpz_class p;  // простое число
//     mpz_class C1; // Ca
//     mpz_class C2; // Cb
//     mpz_class D1; // Da
//     mpz_class D2; // Db
// };

// ShamirKeys generate_shamir_keys(int bit_length = 32);
// void shamir_encrypt_file(
//         const std::string& input_file,
//         const std::string& output_file,
//         const ShamirKeys& keys);
// void shamir_decrypt_file(
//         const std::string& input_file,
//         const std::string& output_file,
//         const ShamirKeys& keys);