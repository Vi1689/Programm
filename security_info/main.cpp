#include "include/info_protection.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>

void print_menu()
{
    std::vector<std::string> s
            = {"Меню:\n",
               "1. Быстрое возведение в степень\n",
               "2. Тест Ферма\n",
               "3. Расширенный алгоритм Евклида\n",
               "4. Дискретный логарифм (Baby-step Giant-step)\n",
               "5. Протокол Диффи–Хеллмана\n",
               "6. Шифровка/расшифровка при помощи шифра Шамира\n",
               "7. Шифровка/расшифровка при помощи шифра Эль-Гамаля\n",
               "8. Шифровка/расшифровка при помощи шифра RSA\n",
               "9. Шифровка/расшифровка при помощи шифра Вернама\n",
               "10. Электронная подпись RSA\n",
               "11. Электронная подпись Эль-Гамаля\n",
               "12. Электронная подпись ГОСТ Р 34.10-94\n",
               "13. Электронная подпись FIPS 186\n",
               "14. Слепая подпись\n",
               "Выберите пункт: "};
    for (const auto& line : s)
        std::cout << line;
}

int main()
{
    srand(time(nullptr));

    int choice;
    print_menu();
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
                      << "Ca = " << keys.Ca << ", Cb = " << keys.Cb << "\n";
        }

        if (mode == 1) {
            std::string infile, outfile;
            std::cout << "Введите имя исходного файла и зашифрованного: ";
            std::cin >> infile >> outfile;

            if (input_choice == 1) {
                std::cout << "Введите p, Ca, Cb: ";
                std::cin >> keys.p >> keys.Ca >> keys.Cb;
            }
            shamir_encrypt_file(infile, outfile, keys);
            std::cout << "Файл зашифрован.\n";
        } else if (mode == 2) {
            std::string infile, outfile;
            std::cout << "Введите имя зашифрованного файла и расшифрованного:";
            std::cin >> infile >> outfile;

            if (input_choice == 1) {
                std::cout << "Введите p, Ca, Cb: ";
                std::cin >> keys.p >> keys.Ca >> keys.Cb;
            }
            shamir_decrypt_file(infile, outfile, keys);
            std::cout << "Файл расшифрован.\n";
        }
    } else if (choice == 7) {
        int mode;
        std::cout << "1. Шифрование файла\n2. "
                     "Дешифрование файла\nВыберите режим: ";
        std::cin >> mode;

        ElGamalKeys keys;

        if (input_choice != 1) {
            keys = generate_elgamal_keys();
            std::cout << "Ключи:\n"
                      << "p = " << keys.p << "\n"
                      << "g = " << keys.g << ", x = " << keys.x << "\n";
        }

        if (mode == 1) {
            std::string infile, outfile;
            std::cout << "Введите имя исходного файла и зашифрованного: ";
            std::cin >> infile >> outfile;

            if (input_choice == 1) {
                std::cout << "Введите p, g, x: ";
                std::cin >> keys.p >> keys.g >> keys.x;
            }
            elgamal_encrypt_file(infile, outfile, keys);
            std::cout << "Файл зашифрован.\n";
        } else if (mode == 2) {
            std::string infile, outfile;
            std::cout << "Введите имя зашифрованного файла и расшифрованного:";
            std::cin >> infile >> outfile;

            if (input_choice == 1) {
                std::cout << "Введите p, g, x: ";
                std::cin >> keys.p >> keys.g >> keys.x;
            }
            elgamal_decrypt_file(infile, outfile, keys);
            std::cout << "Файл расшифрован.\n";
        }
    } else if (choice == 8) {
        int mode;
        std::cout << "1. Шифрование файла\n2. "
                     "Дешифрование файла\nВыберите режим: ";
        std::cin >> mode;

        RSA keys;

        if (input_choice != 1) {
            keys = generate_rsa_keys();
            std::cout << "Ключи:\n"
                      << "p = " << keys.p << "\n"
                      << "q = " << keys.q << ", d = " << keys.d << "\n";
        }

        if (mode == 1) {
            std::string infile, outfile;
            std::cout << "Введите имя исходного файла и зашифрованного: ";
            std::cin >> infile >> outfile;

            if (input_choice == 1) {
                std::cout << "Введите p, q, d: ";
                std::cin >> keys.p >> keys.q >> keys.d;
            }
            rsa_encrypt_file(infile, outfile, keys);
            std::cout << "Файл зашифрован.\n";
        } else if (mode == 2) {
            std::string infile, outfile;
            std::cout << "Введите имя зашифрованного файла и расшифрованного:";
            std::cin >> infile >> outfile;

            if (input_choice == 1) {
                std::cout << "Введите p, q, d: ";
                std::cin >> keys.p >> keys.q >> keys.d;
            }
            rsa_decrypt_file(infile, outfile, keys);
            std::cout << "Файл расшифрован.\n";
        }
    } else if (choice == 9) {
        int mode;
        std::cout << "1. Шифрование файла\n2. "
                     "Дешифрование файла\nВыберите режим: ";
        std::cin >> mode;

        struct keys key {
            0, 0
        };

        if (input_choice != 1) {
            long int p = 0, g = 0, Xa = 0, Xb = 0;
            p = generate_prime(50, 200);
            g = generate_random(2, p - 1);
            Xa = generate_random(2, p - 2);
            Xb = generate_random(2, p - 2);
            key = {Xa, Xb};
            while (diffie_hellman_key_exchange(p, g, &key)) {
                Xa = generate_random(2, p - 2);
                Xb = generate_random(2, p - 2);
                key = {Xa, Xb};
            }
            std::cout << "k = " << key.a << '\n';
        }

        if (mode == 1) {
            std::string infile, outfile;
            std::cout << "Введите имя исходного файла и зашифрованного: ";
            std::cin >> infile >> outfile;

            if (input_choice == 1) {
                std::cout << "Введите k: ";
                std::cin >> key.a;
            }
            vernam_encrypt_file(infile, outfile, key);
            std::cout << "Файл зашифрован.\n";
        } else if (mode == 2) {
            std::string infile, outfile;
            std::cout << "Введите имя зашифрованного файла и расшифрованного:";
            std::cin >> infile >> outfile;

            if (input_choice == 1) {
                std::cout << "Введите k: ";
                std::cin >> key.a;
            }
            vernam_decrypt_file(infile, outfile, key);
            std::cout << "Файл расшифрован.\n";
        }
    } else if (choice == 10) {
        int mode;
        std::cout << "1. Подпись файла\n2. "
                     "Проверка подписи файла\nВыберите режим: ";
        std::cin >> mode;

        RSA keys;

        if (input_choice != 1) {
            keys = generate_rsa_keys();
            std::cout << "Ключи:\n"
                      << "p = " << keys.p << "\n"
                      << "q = " << keys.q << ", d = " << keys.d << "\n";
        }

        if (mode == 1) {
            std::string infile, outfile;
            std::cout << "Введите имя файла который будет подписан и файл с "
                         "подписью: ";
            std::cin >> infile >> outfile;

            if (input_choice == 1) {
                std::cout << "Введите p, q, d: ";
                std::cin >> keys.p >> keys.q >> keys.d;
            }
            rsa_signature(infile, outfile, keys);
            std::cout << "Файл подписан.\n";
        } else if (mode == 2) {
            std::string infile, outfile;
            std::cout << "Введите имя файла для проверки подписи и файл с "
                         "подписью: ";
            std::cin >> infile >> outfile;

            if (input_choice == 1) {
                std::cout << "Введите p, q, d: ";
                std::cin >> keys.p >> keys.q >> keys.d;
            }
            std::string s;
            rsa_signature_check(infile, outfile, keys)
                    ? s = "Подпись корректна"
                    : s = "Подпись не корректна";
            std::cout << s << '\n';
        }
    } else if (choice == 11) {
        int mode;
        std::cout << "1. Подпись файла\n2. "
                     "Проверка подписи файла\nВыберите режим: ";
        std::cin >> mode;

        ElGamalKeys keys;

        if (input_choice != 1) {
            keys = generate_elgamal_keys();
            std::cout << "Ключи:\n"
                      << "p = " << keys.p << "\n"
                      << "g = " << keys.g << ", x = " << keys.x << "\n";
        }

        if (mode == 1) {
            std::string infile, outfile;
            std::cout << "Введите имя файла который будет подписан и файл с "
                         "подписью: ";
            std::cin >> infile >> outfile;

            if (input_choice == 1) {
                std::cout << "Введите p, g, x: ";
                std::cin >> keys.p >> keys.g >> keys.x;
            }
            elgamal_signature(infile, outfile, keys);
            std::cout << "Файл подписан.\n";
        } else if (mode == 2) {
            std::string infile, outfile;
            std::cout << "Введите имя файла для проверки подписи и файл с "
                         "подписью: ";
            std::cin >> infile >> outfile;

            if (input_choice == 1) {
                std::cout << "Введите p, g, x: ";
                std::cin >> keys.p >> keys.g >> keys.x;
            }
            std::string s;
            elgamal_signature_check(infile, outfile, keys)
                    ? s = "Подпись корректна"
                    : s = "Подпись не корректна";
            std::cout << s << '\n';
        }
    } else if (choice == 12) {
        int mode;
        std::cout << "1. Подпись файла\n2. "
                     "Проверка подписи файла\nВыберите режим: ";
        std::cin >> mode;

        GOST94Keys keys;

        if (input_choice != 1) {
            keys = generate_gost94_keys();
            std::cout << "Ключи:\n"
                      << "p = " << keys.p << "\n"
                      << "q = " << keys.q << ", a = " << keys.a << "\n"
                      << "x = " << keys.x << "\n"
                      << "y = " << keys.y << "\n";
        }

        if (mode == 1) {
            std::string infile, outfile;
            std::cout << "Введите имя файла который будет подписан и файл с "
                         "подписью: ";
            std::cin >> infile >> outfile;

            if (input_choice == 1) {
                std::cout << "Введите p, q, a, x, y: ";
                std::cin >> keys.p >> keys.q >> keys.a >> keys.x >> keys.y;
            }
            gost94_signature(infile, outfile, keys);
            std::cout << "Файл подписан.\n";
        } else if (mode == 2) {
            std::string infile, outfile;
            std::cout << "Введите имя файла для проверки подписи и файл с "
                         "подписью: ";
            std::cin >> infile >> outfile;

            if (input_choice == 1) {
                std::cout << "Введите p, q, a, x, y: ";
                std::cin >> keys.p >> keys.q >> keys.a >> keys.x >> keys.y;
            }
            std::string s;
            gost94_signature_check(infile, outfile, keys)
                    ? s = "Подпись корректна"
                    : s = "Подпись не корректна";
            std::cout << s << '\n';
        }
    } else if (choice == 13) {
        int mode;
        std::cout << "1. Подпись файла\n2. "
                     "Проверка подписи файла\nВыберите режим: ";
        std::cin >> mode;

        DSAKeys keys;

        if (input_choice != 1) {
            keys = generate_dsa_keys();
            std::cout << "Ключи:\n"
                      << "p = " << keys.p << "\n"
                      << "q = " << keys.q << ", g = " << keys.g << "\n"
                      << "x = " << keys.x << "\n"
                      << "y = " << keys.y << "\n";
        }

        if (mode == 1) {
            std::string infile, outfile;
            std::cout << "Введите имя файла который будет подписан и файл с "
                         "подписью: ";
            std::cin >> infile >> outfile;

            if (input_choice == 1) {
                std::cout << "Введите p, q, g, x, y: ";
                std::cin >> keys.p >> keys.q >> keys.g >> keys.x >> keys.y;
            }
            dsa_signature(infile, outfile, keys);
            std::cout << "Файл подписан.\n";
        } else if (mode == 2) {
            std::string infile, outfile;
            std::cout << "Введите имя файла для проверки подписи и файл с "
                         "подписью: ";
            std::cin >> infile >> outfile;

            if (input_choice == 1) {
                std::cout << "Введите p, q, g, x, y: ";
                std::cin >> keys.p >> keys.q >> keys.g >> keys.x >> keys.y;
            }
            std::string s;
            dsa_signature_check(infile, outfile, keys)
                    ? s = "Подпись корректна"
                    : s = "Подпись не корректна";
            std::cout << s << '\n';
        }
    } else if (choice == 14) {
        std::cout << "Слепая подпись\n";

        RSA keys;
        long int n;

        if (input_choice != 1) {
            keys = generate_rsa_keys();
            n = keys.p * keys.q;
            std::cout << "Ключи:\n"
                      << "p = " << keys.p << "\n"
                      << "q = " << keys.q << ", d = " << keys.d << "\n";
        }

        if (input_choice == 1) {
            std::cout << "Введите p, q, d: ";
            std::cin >> keys.p >> keys.q >> keys.d;
            n = keys.p * keys.q;
        }

        long int phi = (keys.p - 1) * (keys.q - 1);
        long int e = 65537;
        long int x, y;
        if (e >= phi || gcd_extended(e, phi, x, y) != 1) {
            e = 3;
            while (gcd_extended(e, phi, x, y) != 1) {
                e += 2;
            }
        }

        int voter_id = 1;
        bool end = false;

        while (!end) {
            std::cout << "\n--- Голосующий ID: " << voter_id << " ---\n";
            std::cout << "Выберите вариант:\n";
            std::cout << "1 - Да\n";
            std::cout << "2 - Нет\n";
            std::cout << "3 - Воздержался\n";
            std::cout << "4 - Завершить голосование\n";
            std::cout << "Ваш выбор: ";

            int a;
            std::cin >> a;

            if (a < 1 || a > 4)
                continue;

            if (a == 4)
                break;

            long int m = voter_id * 1000 + a;

            long int blinding_factor = 0, unblinding_factor = 0;

            std::cout << "\n1. Создан бюллетень:\n";
            std::cout << "   ID голосующего: " << voter_id << "\n";
            std::cout << "   Выбор: " << a;
            switch (a) {
            case 1:
                std::cout << " (Да)";
                break;
            case 2:
                std::cout << " (Нет)";
                break;
            case 3:
                std::cout << " (Воздержался)";
                break;
            }
            std::cout << "\n   Исходное сообщение: " << m << "\n";

            // Ослепление сообщения
            auto blinded_message = blind_message(
                    m, e, n, blinding_factor, unblinding_factor);

            std::cout << "\n2. Ослепление сообщения:\n";
            std::cout << "   Blinding factor (r): " << blinding_factor << "\n";
            std::cout << "   Unblinding factor (r⁻¹): " << unblinding_factor
                      << "\n";
            std::cout << "   Ослепленное сообщение (m' = m * r^e mod n): "
                      << blinded_message << "\n";

            // Подпись ослепленного сообщения сервером
            std::cout << "\n3. Подпись сервером:\n";
            std::cout << "   Сервер видит только ослепленное сообщение: "
                      << blinded_message << "\n";
            long int blinded_signature
                    = sign_blinded_message(blinded_message, keys);
            std::cout << "   Подпись ослепленного сообщения (s' = m'^d mod n): "
                      << blinded_signature << "\n";

            // Снятие ослепления
            auto signature = unblind_signature(
                    blinded_signature, unblinding_factor, n);
            std::cout << "\n4. Снятие ослепления:\n";
            std::cout << "   Финальная подпись (s = s' * r⁻¹ mod n): "
                      << signature << "\n";

            // Проверка подписи
            bool signature_valid = verify_blind_signature(m, signature, e, n);

            std::cout << "\n5. Проверка подписи:\n";
            std::cout << "   Проверка: m = s^e mod n\n";
            std::cout << "   " << m << " = " << mod_pow(signature, e, n)
                      << " mod " << n << "\n";
            std::cout << "   Подпись "
                      << (signature_valid ? " КОРРЕКТНА" : " НЕКОРРЕКТНА")
                      << "\n";

            if (signature_valid) {
                std::cout << "    Бюллетень принят!\n";
                voter_id++;
            } else {
                std::cout << "    Бюллетень отклонен!\n";
            }
        }
    } else {
        std::cout << "Неверный выбор!\n";
    }

    return 0;
}
