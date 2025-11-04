#pragma once
#include <climits>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <gmpxx.h>
#include <iomanip>
#include <openssl/sha.h>
#include <random>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

long int generate_random(const long int& min, const long int& max);
long int generate_prime(const long int& min, const long int& max);
std::string calculate_sha256(const std::string& filename);
std::vector<long int> read_hex(const std::string& hex_filename);
bool write_hex(
        const std::vector<long int>& data, const std::string& hex_filename);

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
    long int p;
    long int Ca;
    long int Cb;
};

ShamirKeys generate_shamir_keys(int min_p = 256, int max_p = 1000);
void shamir_encrypt_file(
        const std::string& input_file,
        const std::string& output_file,
        const ShamirKeys& keys);
void shamir_decrypt_file(
        const std::string& input_file,
        const std::string& output_file,
        const ShamirKeys& keys);

// ЛР 5
struct ElGamalKeys {
    long int p;
    long int g;
    long int x;
};

ElGamalKeys generate_elgamal_keys(int min_p = 256, int max_p = 1000);
void elgamal_encrypt_file(
        const std::string& input_file,
        const std::string& output_file,
        const ElGamalKeys& keys);
void elgamal_decrypt_file(
        const std::string& input_file,
        const std::string& output_file,
        const ElGamalKeys& keys);

// ЛР 6
struct RSA {
    long int p;
    long int q;
    long int d;
};

RSA generate_rsa_keys(int min_p = 256, int max_p = 1000);
void rsa_encrypt_file(
        const std::string& input_file,
        const std::string& output_file,
        const RSA& keys);
void rsa_decrypt_file(
        const std::string& input_file,
        const std::string& output_file,
        const RSA& keys);

// ЛР 7
std::vector<unsigned char>
generate_vernama_keys(size_t length, const keys& key);
void vernam_encrypt_file(
        const std::string& input_file,
        const std::string& output_file,
        const keys& key);
void vernam_decrypt_file(
        const std::string& input_file,
        const std::string& output_file,
        const keys& key);

// ЛР 8
void rsa_signature(
        const std::string& input_file,
        const std::string& output_file,
        const RSA& keys);
bool rsa_signature_check(
        const std::string& input_file,
        const std::string& output_file,
        const RSA& keys);

// ЛР 9
void elgamal_signature(
        const std::string& input_file,
        const std::string& output_file,
        const ElGamalKeys& keys);
bool elgamal_signature_check(
        const std::string& input_file,
        const std::string& output_file,
        const ElGamalKeys& keys);

// ЛР 10
struct GOST94Keys {
    long int p; // большое простое число
    long int q; // делитель p - 1
    long int a; // генератор подгруппы
    long int x; // закрытый ключ
    long int y; // открытый ключ (y = a^x mod p)
};
GOST94Keys generate_gost94_keys(int min_p = 256, int max_p = 1000);
void gost94_signature(
        const std::string& input_file,
        const std::string& output_file,
        const GOST94Keys& keys);
bool gost94_signature_check(
        const std::string& input_file,
        const std::string& output_file,
        const GOST94Keys& keys);

// ЛР 11
struct DSAKeys {
    long int p; // большое простое число
    long int q; // простое число, делитель p-1
    long int g; // генератор
    long int x; // закрытый ключ
    long int y; // открытый ключ
};
DSAKeys generate_dsa_keys(int min_p = 256, int max_p = 1000);
void dsa_signature(
        const std::string& input_file,
        const std::string& output_file,
        const DSAKeys& keys);
bool dsa_signature_check(
        const std::string& input_file,
        const std::string& output_file,
        const DSAKeys& keys);

// ЛР 13

long int blind_message(
        long int message,
        long int e,
        long int n,
        long int& blinding_factor,
        long int& unblinding_factor);
long int sign_blinded_message(long int blinded_message, const RSA& keys);
long int unblind_signature(
        long int blinded_signature, long int unblinding_factor, long int n);
bool verify_blind_signature(
        long int message, long int signature, long int e, long int n);