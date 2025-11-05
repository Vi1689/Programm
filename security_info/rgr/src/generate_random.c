#include "../include/info_protection.h"

long int generate_random(const long int min, const long int max)
{
    long int r = min + rand() % (max - min + 1);
    return r;
}