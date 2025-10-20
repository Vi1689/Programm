#include "data_base.h"
#include "my_network.h"
#include "parallelism.h"
#include "server/server.h"
#include <stdio.h>
#include <unistd.h>

extern int g_server_socket;
extern struct thread_pool g_thread_pool;
extern struct data_base *g_database;

void cleanup_server(void) {
  printf("Очистка ресурсов сервера...\n");

  pthread_mutex_lock(&g_thread_pool.queue_mutex);
  g_thread_pool.stop_pool = true;
  pthread_cond_broadcast(&g_thread_pool.cond_nonempty);
  pthread_mutex_unlock(&g_thread_pool.queue_mutex);

  sleep(1);

  thread_pool_destroy(&g_thread_pool);

  if (g_server_socket != -1) {
    delete_sock(g_server_socket);
    g_server_socket = -1;
  }

  if (g_database != NULL) {
    db_destroy(g_database);
    g_database = NULL;
    printf("База данных успешно уничтожена.\n");
  }
  printf("Ресурсы сервера очищены.\n");
}
