#include "include/info_protection.h"
#include "include/my_network.h"
#include <malloc.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define NUM_ROUNDS 20

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
        long client_n = 0, client_v = 0;

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
                    client_n = arr.value[i].n;
                    client_v = arr.value[i].v;
                    break;
                }
            }

            if (found) {
                sprintf(send_buf, "%ld %ld", client_n, client_v);
            } else {
                sprintf(send_buf, "0 0");
            }
            my_send(fd, send_buf, sizeof(send_buf), client_addr);

            if (!found)
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

            if (sscanf(recv_buf, "%ld %ld", &client_n, &client_v) != 2) {
                printf("Неверный формат параметров: %s\n", recv_buf);
                continue;
            }
        } else {
            continue;
        }

        int success_rounds = 0;
        for (int round = 0; round < NUM_ROUNDS; ++round) {
            printf("\n--- Раунд %d ---\n", round + 1);

            bytes = my_recv(fd, recv_buf, sizeof(recv_buf), &client_addr);
            if (bytes <= 0)
                break;

            long x;
            if (sscanf(recv_buf, "commitment %ld", &x) != 1) {
                printf("Неверный формат запроса: %s\n", recv_buf);
                break;
            }

            printf("n = %ld\nv = %ld\nx = %ld\n", client_n, client_v, x);

            char e = (rand() & 1) ? '1' : '0';
            printf("e = %c\n", e);
            sprintf(send_buf, "challenge %c", e);
            my_send(fd, send_buf, sizeof(send_buf), client_addr);

            bytes = my_recv(fd, recv_buf, sizeof(recv_buf), &client_addr);
            if (bytes <= 0)
                break;

            long y;
            if (sscanf(recv_buf, "response %ld", &y) != 1) {
                printf("Неверный формат ответа: %s\n", recv_buf);
                break;
            }

            printf("y = %ld\n", y);

            int verified;
            if (e == '0') {
                verified = (mod_pow(y, 2, client_n) == (x % client_n));
            } else {
                verified
                        = (mod_pow(y, 2, client_n)
                           == ((x * client_v) % client_n));
            }

            sprintf(send_buf, "%s", verified ? "УСПЕШНО" : "НЕУДАЧА");
            my_send(fd, send_buf, sizeof(send_buf), client_addr);

            if (verified) {
                success_rounds++;
                printf("Раунд %d: УСПЕШНО\n", round + 1);
            } else {
                printf("Раунд %d: НЕУДАЧА\n", round + 1);
                break;
            }
        }

        printf("\n=== Результат: %d/%d раундов ===\n",
               success_rounds,
               NUM_ROUNDS);

        if (success_rounds == NUM_ROUNDS) {
            printf("Аутентификация УСПЕШНА\n");
            if (add_client) {
                arr.size++;
                arr.value
                        = realloc(arr.value, arr.size * sizeof(struct client));
                arr.value[arr.size - 1].n = client_n;
                arr.value[arr.size - 1].v = client_v;
                strcpy(arr.value[arr.size - 1].name, name);
                printf("Новый клиент зарегистрирован: %s\n", name);
            }
        } else {
            printf("Аутентификация НЕУДАЧНА\n");
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