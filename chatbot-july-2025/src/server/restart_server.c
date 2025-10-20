#include "server/server.h"
#include <stdio.h>

extern volatile sig_atomic_t g_stop_server;
extern volatile sig_atomic_t g_reload_server;

int restart_server(int port, int num_threads, int max_queue_size) {
  printf("Перезапуск сервера...\n");
  cleanup_server();
  g_stop_server = 0;
  g_reload_server = 0;
  return init_server(port, num_threads, max_queue_size);
}
