#ifndef SIGNAL_HANDLER_H
#define SIGNAL_HANDLER_H

#include <signal.h>

extern volatile sig_atomic_t g_stop_server;
extern volatile sig_atomic_t g_reload_server;

/**
 * @brief Обработчик сигналов для корректного завершения работы и перезагрузки
 * сервера.
 *
 * @param signum Номер полученного сигнала.
 */
void handle_signal(int signum);

/**
 * @brief Устанавливает обработчики сигналов для SIGINT, SIGTERM и SIGUSR1.
 */
void setup_signal_handler(void);

#endif