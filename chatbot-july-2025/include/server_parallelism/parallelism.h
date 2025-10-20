#ifndef PARALLELISM_H
#define PARALLELISM_H

#include <netinet/in.h> // Для struct sockaddr_in
#include <pthread.h>
#include <sodium.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define MAX_UDP_PACKET_SIZE 2048 // Максимальный размер UDP пакета

/**
 * @brief Структура task определяет каждый дескриптор клиента как отдельную
 * задачу. В дальнейшем будет расширяться.
 */
struct task {
  char data_buffer[MAX_UDP_PACKET_SIZE]; // Буфер для принятых данных
  ssize_t data_len;               // Длина принятых данных
  struct sockaddr_in client_addr; // Адрес отправителя
  socklen_t client_addr_len;      // Длина адреса
  struct task *next; /** Служит для перемещения по списку задач. */
};

/**
 * @brief Структура thread_pool определяет как будет происходить перемещение по
 * очереди задач Определяем переменные для синхронизации, максимальную длинну
 * очереди и количество потоков
 */
struct thread_pool {
  pthread_t *threads; /** Массив с нашими потоками. */
  int num_threads;    /** Количество потоков. */

  struct task *task_queue_head; /** Голова нашей очереди. */
  struct task *task_queue_tail; /** Конец очереди. */
  int task_queue_size; /** Текущая длинна очереди. */
  int max_queue_size; /** Максимальная длинна очереди. */

  pthread_mutex_t
      queue_mutex; /** Мьютекс для синхронизации доступа к очереди. */
  pthread_cond_t cond_nonempty; /** Переменная для ожидания. */
  bool stop_pool; /** Переменная для остановки работы потоков. */

  pthread_mutex_t
      database_mutex; /** Мьютекс для синхронизации доступа к g_database. */
};

/**
 * @brief Функция, выполняемая каждым рабочим потоком в пуле.
 * @param arg Указатель на аргументы потока.
 * @return NULL.
 */
void *worker_thread_func(void *arg);

/**
 * @brief Инициализирует и запускает пул потоков.
 *
 * @param pool Указатель на структуру struct thread_pool для инициализации.
 * @param num_threads Количество потоков для создания в пуле.
 * @param max_queue_size Максимальный размер очереди задач.
 */
int thread_pool_init(struct thread_pool *pool, int num_threads,
                     int max_queue_size);

/**
 * @brief Добавляет новую задачу (данные UDP-пакета и адрес отправителя) в
 * очередь пула потоков.
 *
 * @param pool Указатель на структуру struct thread_pool, куда добавляется
 * задача.
 * @param data Указатель на буфер с данными пакета.
 * @param data_len Длина данных в буфере.
 * @param client_addr Указатель на структуру sockaddr_in с адресом отправителя.
 * @param client_addr_len Длина структуры адреса отправителя.
 */
int thread_pool_add_task(struct thread_pool *pool, const char *data,
                         ssize_t data_len,
                         const struct sockaddr_in *client_addr,
                         socklen_t client_addr_len);

/**
 * @brief Ожидает завершения всех потоков в пуле и освобождает связанные
 * ресурсы.
 *
 * @param pool Указатель на структуру struct thread_pool.
 * @return 0 в случае успеха, -1 в случае ошибки.
 */
int thread_pool_destroy(struct thread_pool *pool);

#endif // PARALLELISM_H