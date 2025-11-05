#ifndef INFO_PROTECTION__
#define INFO_PROTECTION__
#include <stdlib.h>

long int generate_random(const long int min, const long int max);
long int generate_prime(const long int min, const long int max);
long int mod_pow(long int a, long int x, long int p);
char prime_number(long int p);
long int gcd_extended(long int a, long int b, long int* x, long int* y);

#endif