#include <cmath>
#include <cstdlib>
#include <iostream>
#include <unordered_map>

long int task_1(long int a, long int x, long int p)
{
    long int out = 1;
    while (x) {
        a %= p;
        if (x & 1)
            out *= a;
        x >>= 1;
        a *= a;
    }
    return out % p;
}

bool task_2(long int p)
{
    for (long int a = 2; a <= p - 2; ++a) {
        if (task_1(a, p - 1, p) != 1)
            return false;
    }

    return true;
}

long long fast_power(long long base, long long exponent, long long modulus)
{
    if (modulus == 1)
        return 0;

    long long result = 1;
    base = base % modulus;

    while (exponent > 0) {
        if (exponent % 2 == 1) {
            result = (result * base) % modulus;
        }
        exponent = exponent >> 1;
        base = (base * base) % modulus;
    }

    return result;
}

long long baby_step_giant_step(long long a, long long b, long long p)
{
    if (a % p == 0) {
        if (b % p == 0)
            return 1;
        return -1;
    }

    long long n = (long long)sqrt(p) + 1;

    std::unordered_map<long long, long long> value_map;
    long long current = 1;

    for (long long j = 0; j < n; ++j) {
        value_map[current] = j;
        current = (current * a) % p;
    }

    long long a_inv_n = fast_power(a, p - 1 - n, p);
    long long gamma = b % p;

    for (long long i = 0; i < n; ++i) {
        if (value_map.find(gamma) != value_map.end()) {
            long long j = value_map[gamma];
            return i * n + j;
        }
        gamma = (gamma * a_inv_n) % p;
    }

    return -1;
}

struct keys {
    long long a, b = 0;
};

long long
diffie_hellman_key_exchange(long long p, long long g, struct keys* key)
{
    if (g >= p)
        return -1;
    long long Ya = task_1(g, key->a, p);
    long long Yb = task_1(g, key->b, p);

    key->a = task_1(Yb, key->a, p);
    key->b = task_1(Ya, key->b, p);

    if (key->a == key->b)
        return 0;

    return -1;
}

int main()
{
    long int p, g, Xa, Xb;
    struct keys key;
    srand(time(NULL));
start1:
    std::cout << "Выберите 'p', 'g', 'Xa', 'Xb':\n"
                 "\t1 - ввод 'p', 'g', 'Xa', 'Xb' с клавиатуры\n"
                 "\t2 - генерация 'p', 'g', 'Xa', 'Xb'\n";
    std::cin >> p;
    if (p == 1) {
        std::cout << "Введите 'p', 'g', 'Xa', 'Xb'\n";
        std::cin >> p >> g >> Xa >> Xb;
        key = {Xa, Xb};
    } else if (p == 2) {
        while (1) {
            while (true) {
                p = rand() % 10000;
                if (task_2(p))
                    break;
            }

            while (true) {
                g = rand() % 1000;
                if (g < p)
                    break;
            }

            Xa = rand() % (p - 2) + 2;
            Xb = rand() % (p - 2) + 2;
            key = {Xa, Xb};
            if (!diffie_hellman_key_exchange(p, g, &key)) {
                printf("p = %ld\ng = %ld\nXa = %ld\nXb = %ld\n", p, g, Xa, Xb);
                break;
            }
        }
    } else {
        std::cout << "Введите по новой\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        goto start1;
    }

    long long x = diffie_hellman_key_exchange(p, g, &key);
    if (x == -1) {
        std::cout << "Ответа нет\n";
    } else {
        std::cout << "Общий ключ - " << key.a << '\n';
    }

    return 0;
}