#include "udp_listener.h"
#include "client/client.h"
#include "error_handler.h"
#include "my_network.h"
#include "server/server.h"
#include <arpa/inet.h>
#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <string.h>

extern int g_server_socket;
extern struct thread_pool g_thread_pool;

void *udp_listener_thread_func(void *arg __attribute__((unused))) {
  struct client_message received_message;
  struct sockaddr_in client_addr;
  socklen_t client_addr_len;
  ssize_t bytes_read;

  printf("UDP Listener: Поток %lu начинает слушать на сокете %d...\n",
         pthread_self(), g_server_socket);

  while (!g_thread_pool.stop_pool) {
    memset(&received_message, 0, sizeof(received_message));
    memset(&client_addr, 0, sizeof(client_addr));
    client_addr_len = sizeof(client_addr);

    bytes_read = my_recv(g_server_socket, (char *)&received_message,
                         sizeof(received_message), &client_addr);

    if (bytes_read > 0) {
      if (bytes_read != sizeof(struct client_message)) {
        ERROR("UDP Listener: Получен пакет неожиданного размера.");
        printf("UDP Listener: Получен пакет от %s:%d, размер %zd байт, "
               "ожидалось %zd.\n",
               inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port),
               bytes_read, sizeof(struct client_message));
        continue;
      }

      printf("UDP Listener: Получено от %s:%d (Логин: \"%s\", Сообщение: "
             "\"%s\")\n",
             inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port),
             received_message.user_login, received_message.message);

      if (thread_pool_add_task(&g_thread_pool, (char *)&received_message,
                               bytes_read, &client_addr,
                               client_addr_len) != 0) {
        ERROR("Не удалось добавить задачу в пул.");
        printf("UDP Listener: Не удалось добавить задачу в пул для пакета от "
               "%s:%d.\n",
               inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
      }
    } else if (bytes_read == 0) {
      printf("UDP Listener: Получена пустая датаграмма.\n");
    } else {
      if (errno != EINTR) {
        ERROR("Ошибка чтения из UDP сокета в потоке-слушателе.");
        printf("UDP Listener: Ошибка чтения из UDP сокета: %s.\n",
               strerror(errno));
      } else {
        printf("UDP Listener: Вызов my_recv прерван сигналом (errno=EINTR).\n");
      }
    }
  }
  printf("UDP Listener: Поток %lu завершает работу.\n", pthread_self());
  return NULL;
}