#include "include/info_protection.h"
#include "include/my_network.h"
#include <stdio.h>
#include <time.h>

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

    long n, v, s, y, r, x;
    char e;

    if (input == 1) {
        printf("Введите s - ");
        scanf("%ld", &s);
        printf("Введите имя - ");
        char name[32];
        scanf("%s", name);
        sprintf(send_buf, "in %s", name);
        my_send(fd, send_buf, sizeof(send_buf), server_addr);
        my_recv(fd, recv_buf, sizeof(recv_buf), &server_addr);

        if (sscanf(recv_buf, "%ld %ld", &n, &v) != 2) {
            printf("Server error: %s\n", recv_buf);
            delete_sock(fd);
            return -1;
        }

    } else if (input == 2) {
        printf("Введите имя - ");
        char name[32];
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

    } else {
        printf("Неправильный выбор)\n");
        delete_sock(fd);
        return 0;
    }

    printf("Client: n = %ld, v = %ld, s = %ld\n", n, v, s);

    // Шаг 1: Клиент отправляет commitment
    r = generate_random(2, n - 1);
    x = mod_pow(r, 2, n);

    sprintf(send_buf, "commitment %ld %ld %ld", x, v, n);
    printf("Client sending: %s\n", send_buf);
    my_send(fd, send_buf, sizeof(send_buf), server_addr);

    // Шаг 2: Клиент получает challenge
    my_recv(fd, recv_buf, sizeof(recv_buf), &server_addr);
    printf("Client received: %s\n", recv_buf);

    sscanf(recv_buf, "challenge %c", &e);

    // Шаг 3: Клиент вычисляет и отправляет response
    if (e == '0') {
        y = r;
    } else if (e == '1') {
        y = (r * s) % n;
    } else {
        printf("Invalid challenge: %c\n", e);
        delete_sock(fd);
        return -1;
    }

    sprintf(send_buf, "response %ld", y);
    printf("Client sending: %s\n", send_buf);
    my_send(fd, send_buf, sizeof(send_buf), server_addr);

    // Шаг 4: Клиент получает результат верификации
    my_recv(fd, recv_buf, sizeof(recv_buf), &server_addr);
    printf("Authentication result: %s\n", recv_buf);

    delete_sock(fd);
    return 0;
}