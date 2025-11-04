#include "../include/info_protection.hpp"

long int blind_message(
        long int message,
        long int e,
        long int n,
        long int& blinding_factor,
        long int& unblinding_factor)
{
    // Выбираем случайный blinding factor, взаимно простой с n
    long int temp;
    do {
        blinding_factor = generate_random(2, n - 1);
    } while (gcd_extended(blinding_factor, n, unblinding_factor, temp) != 1);

    // Вычисляем unblinding factor как обратный элемент
    gcd_extended(blinding_factor, n, unblinding_factor, temp);
    unblinding_factor = (unblinding_factor % n + n) % n;

    // Ослепляем сообщение: blinded = message * (blinding_factor^e) mod n
    long int blinded = (message * mod_pow(blinding_factor, e, n)) % n;
    return blinded;
}