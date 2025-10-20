#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "error_handler.h"
#include "signal_handler.h"

volatile sig_atomic_t g_stop_server = 0;
volatile sig_atomic_t g_reload_server = 0;

void handle_signal(int signum) {
  if (signum == SIGINT || signum == SIGTERM) {
    printf("\nПолучен сигнал завершения (%d). Завершение работы сервера...\n",
           signum);
    g_stop_server = 1;
  } else if (signum == SIGUSR1) {
    printf("\nПолучен сигнал SIGUSR1. Перезагрузка сервера...\n");
    g_reload_server = 1;
  }
}

void setup_signal_handler(void) {
  struct sigaction sa;
  memset(&sa, 0, sizeof(sa));
  sa.sa_handler = handle_signal;
  sigemptyset(&sa.sa_mask);
  sa.sa_flags = 0;

  if (sigaction(SIGINT, &sa, NULL) == -1) {
    ERROR("Ошибка установки обработчика SIGINT");
    exit(EXIT_FAILURE);
  }
  if (sigaction(SIGTERM, &sa, NULL) == -1) {
    ERROR("Ошибка установки обработчика SIGTERM");
    exit(EXIT_FAILURE);
  }
  if (sigaction(SIGUSR1, &sa, NULL) == -1) {
    ERROR("Ошибка установки обработчика SIGUSR1");
    exit(EXIT_FAILURE);
  }
}