#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "server/server.h"
#include "server/signal_handler.h"

#define DEFAULT_PORT 8080
#define DEFAULT_THREADS 10
#define DEFAULT_QUEUE_SIZE 30

extern volatile sig_atomic_t g_stop_server;
extern volatile sig_atomic_t g_reload_server;

int main(void) {
  int port = DEFAULT_PORT;
  int num_threads = DEFAULT_THREADS;
  int max_queue_size = DEFAULT_QUEUE_SIZE;

  setup_signal_handler();

  while (true) {
    if (init_server(port, num_threads, max_queue_size) != 0) {
      fprintf(
          stderr,
          "Критическая ошибка: Не удалось инициализировать сервер. Выход.\n");
      return EXIT_FAILURE;
    }

    run_server_loop();

    if (g_stop_server) {
      printf("Сервер останавливается по запросу.\n");
      break;
    } else if (g_reload_server) {
      printf("Сервер перезагружается...\n");
      if (restart_server(port, num_threads, max_queue_size) != 0) {
        fprintf(
            stderr,
            "Критическая ошибка: Не удалось перезапустить сервер. Выход.\n");
        return EXIT_FAILURE;
      }
    }
  }

  cleanup_server();
  printf("Сервер успешно завершил работу.\n");

  return EXIT_SUCCESS;
}
