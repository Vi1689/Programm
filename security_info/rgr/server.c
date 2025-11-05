#include "include/info_protection.h"
#include "include/my_network.h"
#include <malloc.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

struct client {
    long v, n;
    char name[32];
};

struct clients {
    struct client* value;
    size_t size;
};

char end = 0;

void my_signal_handler(int sig)
{
    end = 1;
}

int main()
{
    struct sigaction sa;
    sa.sa_handler = my_signal_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("sigaction");
        return -1;
    }

    int fd = create_sock(PORT_SERV, IP_SERV);
    if (fd < 0) {
        printf("Не удалось создать сокет\n");
        return -1;
    }

    srand(time(NULL));

    char send_buf[100] = {0};
    char recv_buf[100] = {0};

    struct clients arr = {NULL, 0};

    printf("Сервер запущен\n");

    while (!end) {
        struct sockaddr_in client_addr = {0};

        char add_client = 0;
        char name[32];

        int bytes = my_recv(fd, recv_buf, sizeof(recv_buf), &client_addr);
        if (bytes <= 0)
            continue;

        if (strstr(recv_buf, "in ")) {
            strcpy(name, recv_buf + strlen("in "));

            int found = 0;
            size_t i;
            for (i = 0; i < arr.size; ++i) {
                if (!strcmp(arr.value[i].name, name)) {
                    found = 1;
                    break;
                }
            }

            if (found) {
                sprintf(send_buf, "%ld %ld", arr.value[i].n, arr.value[i].v);
            } else {
                sprintf(send_buf, "0 0");
            }
            my_send(fd, send_buf, sizeof(send_buf), client_addr);
            continue;

        } else if (strstr(recv_buf, "reg ") == recv_buf) {
            strcpy(name, recv_buf + strlen("reg "));
            int found = 0;
            size_t i;
            for (i = 0; i < arr.size; ++i) {
                if (!strcmp(arr.value[i].name, name)) {
                    found = 1;
                    break;
                }
            }

            if (found) {
                my_send(fd, "Yes", sizeof("Yes"), client_addr);
                continue;
            } else {
                my_send(fd, "No", sizeof("No"), client_addr);
            }

            add_client = 1;

            bytes = my_recv(fd, recv_buf, sizeof(recv_buf), &client_addr);
            if (bytes <= 0)
                continue;
        }

        // Обработка commitment
        long x, v, n;
        if (sscanf(recv_buf, "commitment %ld %ld %ld", &x, &v, &n) != 3) {
            printf("Неверный формат запроса: %s\n", recv_buf);
            continue;
        }

        printf("n = %ld\nv = %ld\nx = %ld\n", n, v, x);

        // Шаг 2: Сервер отправил challenge
        char e = (rand() & 1) ? '1' : '0';
        printf("e = %c\n", e);
        sprintf(send_buf, "challenge %c", e);
        my_send(fd, send_buf, sizeof(send_buf), client_addr);

        // Шаг 3: Сервер получает response
        bytes = my_recv(fd, recv_buf, sizeof(recv_buf), &client_addr);
        if (bytes <= 0)
            continue;

        long y;
        if (sscanf(recv_buf, "response %ld", &y) != 1) {
            printf("Неверный формат ответа: %s\n", recv_buf);
            continue;
        }

        printf("y = %ld\n", y);

        // Шаг 4: Сервер проверяет response
        int verified;
        if (e == '0') {
            verified = (mod_pow(y, 2, n) == (x % n));
        } else {
            verified = (mod_pow(y, 2, n) == ((x * v) % n));
        }

        sprintf(send_buf, "%s", verified ? "УСПЕШНО" : "НЕУДАЧА");
        my_send(fd, send_buf, sizeof(send_buf), client_addr);

        printf("Аутентификация %s\n", verified ? "УСПЕШНО" : "НЕУДАЧА");

        if (verified && add_client) {
            arr.size++;
            arr.value = realloc(arr.value, arr.size * sizeof(struct client));
            arr.value[arr.size - 1].n = n;
            arr.value[arr.size - 1].v = v;
            strcpy(arr.value[arr.size - 1].name, name);

            printf("Новый клиент зарегистрирован: %s\n", name);
        }

        printf("Текущие клиенты:\n");
        for (size_t i = 0; i < arr.size; ++i) {
            printf("Имя - %s, V - %ld, N - %ld\n",
                   arr.value[i].name,
                   arr.value[i].v,
                   arr.value[i].n);
        }
        printf("---\n");
    }

    free(arr.value);
    printf("Сервер выключен\n");
    delete_sock(fd);
    return 0;
}