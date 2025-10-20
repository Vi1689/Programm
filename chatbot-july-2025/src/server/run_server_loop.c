#include "server/server.h"
#include <stdio.h>
#include <unistd.h>

extern volatile sig_atomic_t g_stop_server;
extern volatile sig_atomic_t g_reload_server;

int run_server_loop(void) {
  while (!g_stop_server && !g_reload_server) {
    sleep(1);
  }
  return 0;
}
