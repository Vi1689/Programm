#include "../include/info_protection.hpp"

long int unblind_signature(
        long int blinded_signature, long int unblinding_factor, long int n)
{
    // signature = blinded_signature * unblinding_factor mod n
    return (blinded_signature * unblinding_factor) % n;
}