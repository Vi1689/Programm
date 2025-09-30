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

long int generate_random(const long int& min, const long int& max);
long int generate_prime(const long int& min, const long int& max);

// ЛР1
long int mod_pow(long int a, long int x, long int p);
bool prime_number(long int p);
long int gcd_extended(long int a, long int b, long int& x, long int& y);

// ЛР2
long int baby_step_giant_step(long int a, long int y, long int p);

// ЛР3
struct keys {
    long int a, b = 0;
};
long int diffie_hellman_key_exchange(long int p, long int g, struct keys* key);

// ЛР4
struct ShamirKeys {
    long int p; // простое число
    long int Ca;
    long int Cb;
    long int Da;
    long int Db;
};

ShamirKeys generate_shamir_keys(int min_p = 256, int max_p = 5000);
void shamir_encrypt_file(
        const std::string& input_file,
        const std::string& output_file,
        const ShamirKeys& keys);
void shamir_decrypt_file(
        const std::string& input_file,
        const std::string& output_file,
        const ShamirKeys& keys);