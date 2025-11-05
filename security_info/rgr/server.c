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
        printf("Failed to create socket\n");
        return -1;
    }

    srand(time(NULL));

    char send_buf[100] = {0};
    char recv_buf[100] = {0};

    struct clients arr = {NULL, 0};

    printf("Server started\n");

    while (!end) {
        struct sockaddr_in client_addr = {0};

        char add_client = 0;
        char name[32];

        printf("Server waiting for message...\n");
        int bytes = my_recv(fd, recv_buf, sizeof(recv_buf), &client_addr);
        if (bytes <= 0)
            continue;

        printf("Server received: %s\n", recv_buf);

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
            printf("Server received commitment: %s\n", recv_buf);
        }

        // Обработка commitment
        long x, v, n;
        if (sscanf(recv_buf, "commitment %ld %ld %ld", &x, &v, &n) != 3) {
            printf("Invalid commitment format: %s\n", recv_buf);
            continue;
        }

        // Шаг 2: Сервер отправляет challenge
        char e = (rand() & 1) ? '1' : '0';
        sprintf(send_buf, "challenge %c", e);
        printf("Server sending: %s\n", send_buf);
        my_send(fd, send_buf, sizeof(send_buf), client_addr);

        // Шаг 3: Сервер получает response
        bytes = my_recv(fd, recv_buf, sizeof(recv_buf), &client_addr);
        if (bytes <= 0)
            continue;
        printf("Server received: %s\n", recv_buf);

        long y;
        if (sscanf(recv_buf, "response %ld", &y) != 1) {
            printf("Invalid response format: %s\n", recv_buf);
            continue;
        }

        // Шаг 4: Сервер проверяет response
        int verified;
        if (e == '0') {
            verified = (mod_pow(y, 2, n) == (x % n));
        } else {
            verified = (mod_pow(y, 2, n) == ((x * v) % n));
        }

        sprintf(send_buf, "%s", verified ? "SUCCESS" : "FAIL");
        printf("Server sending result: %s\n", send_buf);
        my_send(fd, send_buf, sizeof(send_buf), client_addr);

        printf("Authentication %s\n", verified ? "SUCCESS" : "FAIL");

        if (verified && add_client) {
            arr.size++;
            arr.value = realloc(arr.value, arr.size * sizeof(struct client));
            arr.value[arr.size - 1].n = n;
            arr.value[arr.size - 1].v = v;
            strcpy(arr.value[arr.size - 1].name, name);

            printf("New client registered: %s\n", name);
        }

        printf("Current clients:\n");
        for (size_t i = 0; i < arr.size; ++i) {
            printf("Name - %s, V - %ld, N - %ld\n",
                   arr.value[i].name,
                   arr.value[i].v,
                   arr.value[i].n);
        }
        printf("---\n");
    }

    free(arr.value);
    printf("The server is turned off\n");
    delete_sock(fd);
    return 0;
}