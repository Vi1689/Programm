#include <algorithm>
#include <iostream>
#include <random>
#include <vector>

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

long int my_pow(long int a, long int x, long int p, long int y)
{
    long int out = 1;
    while (x) {
        a %= p;
        if (x & 1)
            out *= a;
        x >>= 1;
        a *= a;
    }
    return (out * y) % p;
}

long int task_1_1(long int a, long int y, long int p)
{
    long int m = std::ceil(std::sqrt(p)), k = m;

    std::vector<long int> baby, giga;
    baby.reserve(m);
    giga.reserve(k);

    for (long int i = 0; i < m; ++i) {
        baby.push_back(my_pow(a, i, p, y));
        giga.push_back(task_1(a, m * (i + 1), p));
    }

    for (unsigned long int i = 0; i < baby.size(); ++i) {
        for (unsigned long int j = 0; j < giga.size(); ++j) {
            if (baby[j] == giga[i]) {
                if (task_1(a, (i + 1) * m - j, p) == y)
                    return ((i + 1) * m - j);
            }
        }
    }

    return -1;
}

int main()
{
    long int y, a, p;

    srand(time(NULL));
start1:
    std::cout << "Выберите 'a', 'y', 'p':\n"
                 "\t1 - ввод 'a', 'y', 'p' с клавиатуры\n"
                 "\t2 - генерация 'a', 'y', 'p'\n";
    std::cin >> a;
    if (a == 1) {
        std::cout << "Введите 'a', 'y', 'p'\n";
        std::cin >> a >> y >> p;
    } else if (a == 2) {
        while (true) {
            p = rand() % 1000000000;
            if (task_2(p))
                break;
        }

        while (true) {
            a = rand() % 1000000000;
            if (a < p)
                break;
        }
        y = rand() % 1000000000;

        printf("a = %ld\np = %ld\ny = %ld\n", a, p, y);
    } else {
        std::cout << "Введите по новой\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        goto start1;
    }

    long int x = task_1_1(a, y, p);
    if (x == -1) {
        std::cout << "Ответа нет\n";
    } else {
        std::cout << "Ответ: x = " << x << '\n';
    }

    return 0;
}