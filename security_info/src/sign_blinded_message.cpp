#include "../include/info_protection.hpp"

long int sign_blinded_message(long int blinded_message, const RSA& keys)
{
    long int n = keys.p * keys.q;
    // Подписываем ослепленное сообщение: signed_blinded = blinded_message^d mod
    // n
    return mod_pow(blinded_message, keys.d, n);
}