#include "data_base.h"
#include "error_handler.h"
#include "my_network.h"
#include "parallelism.h"
#include "server/server.h"
#include "server/signal_handler.h"
#include "server/udp_listener.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>

int g_server_socket;
struct thread_pool g_thread_pool;
struct data_base *g_database;

int init_server(int port, int num_threads, int max_queue_size) {
  g_database = db_create();
  if (g_database == NULL) {
    ERROR("Ошибка инициализации базы данных.");
    return -1;
  }
  printf("База данных успешно инициализирована.\n");

  g_server_socket = create_sock(port, "172.18.0.1");
  if (g_server_socket == -1) {
    ERROR("Ошибка создания UDP сокета");
    db_destroy(g_database);
    g_database = NULL;
    return -1;
  }

  int optval = 1;
  if (setsockopt(g_server_socket, SOL_SOCKET, SO_REUSEADDR, &optval,
                 sizeof(optval)) < 0) {
    ERROR("setsockopt SO_REUSEADDR failed");
    delete_sock(g_server_socket);
    db_destroy(g_database);
    return -1;
  }

  if (sodium_init() == -1) {
    ERROR("sodium_init");
    delete_sock(g_server_socket);
    db_destroy(g_database);
    return -1;
  }

  if (thread_pool_init(&g_thread_pool, num_threads, max_queue_size) != 0) {
    ERROR("Не удалось инициализировать пул потоков.");
    delete_sock(g_server_socket);
    g_server_socket = -1;
    db_destroy(g_database);
    g_database = NULL;
    return -1;
  }

  pthread_t listener_tid;
  if (pthread_create(&listener_tid, NULL, udp_listener_thread_func, NULL) !=
      0) {
    ERROR("Не удалось создать поток-слушатель UDP.");
    delete_sock(g_server_socket);
    g_server_socket = -1;
    db_destroy(g_database);
    g_database = NULL;
    thread_pool_destroy(&g_thread_pool);
    return -1;
  }
  pthread_detach(listener_tid);

  printf("UDP Сервер запущен на порту %d с %d рабочими потоками. Ожидание "
         "данных...\n",
         port, num_threads);
  return 0;
}
