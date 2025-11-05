#include "include/info_protection.h"
#include "include/my_network.h"
#include <stdio.h>
#include <time.h>

#define NUM_ROUNDS 20

int main()
{
    int fd = create_sock(PORT_CLIENT, "0.0.0.0");
    struct sockaddr_in server_addr;
    fill_sockaddr(&server_addr, PORT_SERV, IP_SERV);

    srand(time(NULL));

    char send_buf[100] = {0};
    char recv_buf[100] = {0};

    int input;
    printf("Выберите режим: \n1. Вход\n2. Регистрация\n");
    scanf("%d", &input);

    long n, v, s;
    char name[32];

    if (input == 1) {
        printf("Введите s - ");
        scanf("%ld", &s);
        printf("Введите имя - ");
        scanf("%s", name);
        sprintf(send_buf, "in %s", name);
        my_send(fd, send_buf, sizeof(send_buf), server_addr);
        my_recv(fd, recv_buf, sizeof(recv_buf), &server_addr);

        if (sscanf(recv_buf, "%ld %ld", &n, &v) != 2) {
            printf("Ошибка сервера: %s\n", recv_buf);
            delete_sock(fd);
            return -1;
        }

        if (!n && !v) {
            printf("Такого имени нет\n");
            delete_sock(fd);
            return 0;
        }

    } else if (input == 2) {
        printf("Введите имя - ");
        scanf("%s", name);
        sprintf(send_buf, "reg %s", name);
        my_send(fd, send_buf, sizeof(send_buf), server_addr);

        // Генерация простых чисел
        long p = generate_prime(3, 1000);
        long q = generate_prime(3, 1000);
        while (q == p)
            q = generate_prime(3, 1000);

        n = p * q;

        long tmp_x, tmp_y;

        // Генерация секрета s
        do {
            s = generate_random(2, n - 1);
        } while (gcd_extended(s, n, &tmp_x, &tmp_y) != 1);

        v = mod_pow(s, 2, n);
        my_recv(fd, recv_buf, sizeof(recv_buf), &server_addr);

        if (!strcmp(recv_buf, "Yes")) {
            printf("Такое имя уже есть\n");
            delete_sock(fd);
            return 0;
        }

        // Отправляем параметры серверу
        sprintf(send_buf, "%ld %ld", n, v);
        my_send(fd, send_buf, sizeof(send_buf), server_addr);

    } else {
        printf("Неправильный выбор)\n");
        delete_sock(fd);
        return 0;
    }

    printf("n = %ld\nv = %ld\ns = %ld\n", n, v, s);

    int success_rounds = 0;
    for (int round = 0; round < NUM_ROUNDS; ++round) {
        printf("\n--- Раунд %d ---\n", round + 1);

        long r = generate_random(2, n - 1);
        long x = mod_pow(r, 2, n);

        printf("r = %ld\nx = %ld\n", r, x);

        sprintf(send_buf, "commitment %ld", x);
        my_send(fd, send_buf, sizeof(send_buf), server_addr);

        my_recv(fd, recv_buf, sizeof(recv_buf), &server_addr);

        char e;
        sscanf(recv_buf, "challenge %c", &e);

        printf("e = %c\n", e);

        long y;
        if (e == '0') {
            y = r;
        } else if (e == '1') {
            y = (r * s) % n;
        } else {
            printf("Неверный вызов: %c\n", e);
            break;
        }

        printf("y = %ld\n", y);

        sprintf(send_buf, "response %ld", y);
        my_send(fd, send_buf, sizeof(send_buf), server_addr);

        my_recv(fd, recv_buf, sizeof(recv_buf), &server_addr);

        if (strcmp(recv_buf, "УСПЕШНО") == 0) {
            success_rounds++;
            printf("Раунд %d: УСПЕШНО\n", round + 1);
        } else {
            printf("Раунд %d: НЕУДАЧА\n", round + 1);
            break;
        }
    }

    printf("\n=== Финальный результат: %d/%d раундов ===\n",
           success_rounds,
           NUM_ROUNDS);

    if (success_rounds == NUM_ROUNDS) {
        printf("Аутентификация УСПЕШНА!\n");
    } else {
        printf("Аутентификация НЕУДАЧНА!\n");
    }

    delete_sock(fd);
    return 0;
}