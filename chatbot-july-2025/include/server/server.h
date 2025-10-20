#ifndef SERVER_H
#define SERVER_H

#include "data_base.h"   // Для struct data_base
#include "parallelism.h" // Для struct thread_pool
#include <netinet/in.h>  // Для struct sockaddr_in
#include <signal.h>      // Для sig_atomic_t
#include <stdbool.h>     // Для bool

// Глобальные переменные сервера, доступные извне библиотеки
extern int g_server_socket;
extern struct thread_pool g_thread_pool;
extern struct data_base *g_database;
extern volatile sig_atomic_t g_stop_server;
extern volatile sig_atomic_t g_reload_server;

/**
 * @brief Инициализирует сервер: создает сокет, привязывает его, и
 * инициализирует пул потоков.
 *
 * @param port Порт для прослушивания.
 * @param num_threads Количество потоков в пуле.
 * @param max_queue_size Максимальный размер очереди задач.
 * @return 0 в случае успеха, -1 в случае ошибки.
 */
int init_server(int port, int num_threads, int max_queue_size);

/**
 * @brief Очищает все ресурсы сервера: закрывает сокеты и уничтожает пул
 * потоков.
 */
void cleanup_server();

/**
 * @brief Основной цикл работы сервера.
 * В этой блокирующей модели, основной поток просто ожидает сигналов.
 * Прием и обработка данных происходит в рабочих потоках.
 *
 * @return 0 в случае нормального завершения, -1 в случае критической ошибки.
 */
int run_server_loop();

/**
 * @brief Перезапускает сервер: очищает старые ресурсы и инициализирует новые.
 *
 * @param port Порт для прослушивания.
 * @param num_threads Количество потоков в пуле.
 * @param max_queue_size Максимальный размер очереди задач.
 * @return 0 в случае успеха, -1 в случае ошибки.
 */
int restart_server(int port, int num_threads, int max_queue_size);

#endif
