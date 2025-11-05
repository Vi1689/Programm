#include "../include/info_protection.hpp"

bool verify_blind_signature(
        long int message, long int signature, long int e, long int n)
{
    // message == signature^e mod n
    long int decrypted = mod_pow(signature, e, n);
    return decrypted == message;
}