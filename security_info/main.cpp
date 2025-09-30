#include "include/info_protection.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>

int main()
{
    srand(time(nullptr));

    int choice;
    std::cout << "Меню:\n";
    std::cout << "1. Быстрое возведение в степень\n";
    std::cout << "2. Тест Ферма\n";
    std::cout << "3. Расширенный алгоритм Евклида\n";
    std::cout << "4. Дискретный логарифм (Baby-step Giant-step)\n";
    std::cout << "5. Протокол Диффи–Хеллмана\n";
    std::cout << "6. Шифровка/расшифровка при помощи шифра Шамира\n";
    std::cout << "Выберите пункт: ";
    std::cin >> choice;

    int input_choice;
    std::cout << "1 - Ввести вручную, 2 - Сгенерировать автоматически: ";
    std::cin >> input_choice;

    if (choice == 1) {
        long int a, x, p;
        if (input_choice == 1) {
            std::cout << "Введите a, x, p: ";
            std::cin >> a >> x >> p;
        } else {
            a = generate_random(2, 100);
            x = generate_random(2, 100);
            p = generate_random(2, 100);
            std::cout << "Сгенерировано: a=" << a << ", x=" << x << ", p=" << p
                      << "\n";
        }
        std::cout << "Результат: " << mod_pow(a, x, p) << "\n";
    } else if (choice == 2) {
        long int p;
        if (input_choice == 1) {
            std::cout << "Введите число p: ";
            std::cin >> p;
        } else {
            p = generate_prime(2, 200);
            std::cout << "Сгенерировано простое число p=" << p << "\n";
        }
        std::cout << (prime_number(p) ? "Вероятно простое\n" : "Составное\n");
    } else if (choice == 3) {
        long int a, b, x, y;
        if (input_choice == 1) {
            std::cout << "Введите a, b: ";
            std::cin >> a >> b;
        } else {
            a = generate_prime(2, 100);
            b = generate_prime(2, 100);
            std::cout << "Сгенерировано: a=" << a << ", b=" << b << "\n";
        }
        long int g = gcd_extended(a, b, x, y);
        std::cout << "НОД = " << g << ", x = " << x << ", y = " << y << "\n";
    } else if (choice == 4) {
        long int a, y, p;
        if (input_choice == 1) {
            std::cout << "Решаем y = a^x mod p\nВведите a, y, p: ";
            std::cin >> a >> y >> p;
        } else {
            a = generate_prime(2, 50);
            p = generate_prime(50, 200);
            long int x = generate_random(2, 10);
            y = mod_pow(a, x, p);
            std::cout << "Сгенерировано: a=" << a << ", y=" << y << ", p=" << p
                      << "\n";
        }
        try {
            long int x = baby_step_giant_step(a, y, p);
            std::cout << "x = " << x << "\n";
        } catch (const std::exception& e) {
            std::cerr << e.what() << "\n";
        }
    } else if (choice == 5) {
        long int p, g, Xa, Xb;
        if (input_choice == 1) {
            std::cout << "Введите p, g, Xa, Xb: ";
            std::cin >> p >> g >> Xa >> Xb;
        } else {
            p = generate_prime(50, 200);
            g = generate_random(2, p - 1);
            Xa = generate_random(2, p - 2);
            Xb = generate_random(2, p - 2);
            std::cout << "Сгенерировано: p=" << p << ", g=" << g
                      << ", Xa=" << Xa << ", Xb=" << Xb << "\n";
        }
        try {
            struct keys key = {Xa, Xb};
            long int x = diffie_hellman_key_exchange(p, g, &key);
            if (x == -1) {
                std::cout << "Ответа нет\n";
            } else {
                std::cout << "Общий ключ - " << key.a << '\n';
            }
        } catch (const std::exception& e) {
            std::cerr << e.what() << "\n";
        }
    } else if (choice == 6) {
        int mode;
        std::cout << "1. Шифрование файла\n2. "
                     "Дешифрование файла\nВыберите режим: ";
        std::cin >> mode;

        ShamirKeys keys;

        if (input_choice != 1) {
            keys = generate_shamir_keys();
            std::cout << "Ключи:\n"
                      << "p = " << keys.p << "\n"
                      << "Ca = " << keys.Ca << ", Da = " << keys.Da << "\n"
                      << "Cb = " << keys.Cb << ", Db = " << keys.Db << "\n";
        }

        if (mode == 1) {
            std::string infile, outfile;
            std::cout << "Введите имя исходного файла и зашифрованного: ";
            std::cin >> infile >> outfile;

            if (input_choice == 1) {
                std::cout << "Введите p, Ca, Cb, Da, Db: ";
                std::cin >> keys.p >> keys.Ca >> keys.Cb >> keys.Da >> keys.Db;
            }
            shamir_encrypt_file(infile, outfile, keys);
            std::cout << "Файл зашифрован.\n";
        } else if (mode == 2) {
            std::string infile, outfile;
            std::cout << "Введите имя зашифрованного файла и расшифрованного:";
            std::cin >> infile >> outfile;

            if (input_choice == 1) {
                std::cout << "Введите p, Ca, Cb, Da, Db: ";
                std::cin >> keys.p >> keys.Ca >> keys.Cb >> keys.Da >> keys.Db;
            }
            shamir_decrypt_file(infile, outfile, keys);
            std::cout << "Файл расшифрован.\n";
        }
    } else {
        std::cout << "Неверный выбор!\n";
    }

    return 0;
}
