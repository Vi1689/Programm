#include <cstdlib>
#include <iostream>
#include <limits>
#include <vector>

int task_1(int a, int x, int p)
{
    int out = 1;
    while (x) {
        a %= p;
        if (x & 1)
            out *= a;
        x >>= 1;
        a *= a;
    }
    return out % p;
}

bool task_2(int p)
{
    for (int a = 2; a <= p - 2; ++a) {
        if (task_1(a, p - 1, p) != 1)
            return false;
    }

    return true;
}

void task_3(int a, int b, std::vector<int>& t)
{
    std::vector<int> u(3), v(3);
    u[0] = a, u[1] = 1, u[2] = 0;
    v[0] = b, v[1] = 0, v[2] = 1;
    if (a < b) {
        std::swap(u, v);
    }

    while (t[0] != 1) {
        int q = u[0] / v[0], tmp = t[0];
        t[0] = u[0] % v[0];
        if (t[0]) {
            t[1] = u[1] - q * v[1];
            t[2] = u[2] - q * v[2];
        } else {
            t[0] = tmp;
            break;
        }
        std::swap(u, v);
        v = t;
    }
}

int main()
{
    int a, x, p;
start:
    std::cout << "Выберите задание:\n"
                 "\t1 - первое\n"
                 "\t2 - второе\n"
                 "\t3 - третье\n";
    std::cin >> a;
    if (a == 1) {
        std::cout << "Первое задание\nВведите 'a', 'x', 'p'\n";
        std::cin >> a >> x >> p;
        std::cout << task_1(a, x, p) << '\n';
    } else if (a == 2) {
        std::cout << "Второе задание\nВведите число\n";
        std::cin >> a;
        std::cout << (task_2(a) ? "Простое" : "Не простое") << '\n';
    } else if (a == 3) {
        std::vector<int> tmp(3);
        srand(time(NULL));
    start1:
        std::cout << "Третье задание\nВыберите 'a' и 'b':\n"
                     "\t1 - ввод 'a' и 'b' с клавиатуры\n"
                     "\t2 - генерация 'a' и 'b'\n"
                     "\t3 - генерация 'a' и 'b', что бы они были простыми "
                     "числами\n";
        std::cin >> a;
        if (a == 1) {
            std::cout << "Введите 'a' и 'b'\n";
            std::cin >> a >> x;
        } else if (a == 2) {
            a = rand() % 1000000000;
            x = rand() % 1000000000;
        } else if (a == 3) {
            while (true) {
                a = rand() % 1000000000;
                if (task_2(a))
                    break;
            }
            while (true) {
                x = rand() % 1000000000;
                if (task_2(x))
                    break;
            }
        } else {
            std::cout << "Введите по новой\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            goto start1;
        }
        task_3(a, x, tmp);
        std::cout << "a = " << a << " b = " << x << "\nnod = " << tmp[0]
                  << " x = " << tmp[1] << " y = " << tmp[2] << '\n';
    } else {
        std::cout << "Введите по новой\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        goto start;
    }
    return 0;
}