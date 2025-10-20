#include "error_handler.h"
#include "parallelism.h"
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int thread_pool_init(struct thread_pool *pool, int num_threads,
                     int max_queue_size) {
  if (pool == NULL || num_threads <= 0 || max_queue_size <= 0) {
    ERROR("Ошибка: переданы неверные аргументы в thread_pool_init");
    exit(EXIT_FAILURE);
  }

  pool->num_threads = num_threads;
  pool->max_queue_size = max_queue_size;
  pool->task_queue_head = NULL;
  pool->task_queue_tail = NULL;
  pool->task_queue_size = 0;
  pool->stop_pool = false;

  if (pthread_mutex_init(&pool->queue_mutex, NULL) != 0) {
    ERROR("Ошибка инициализации мьютекса pool->queue_mutex");
    exit(EXIT_FAILURE);
  }

  if (pthread_cond_init(&pool->cond_nonempty, NULL) != 0) {
    ERROR("Ошибка инициализации cond_nonempty");
    pthread_mutex_destroy(&pool->queue_mutex);
    exit(EXIT_FAILURE);
  }

  if (pthread_mutex_init(&pool->database_mutex, NULL) != 0) {
    ERROR("Ошибка инициализации мьютекса pool->database_mutex");
    pthread_mutex_destroy(&pool->queue_mutex);
    pthread_cond_destroy(&pool->cond_nonempty);
    exit(EXIT_FAILURE);
  }

  pool->threads = (pthread_t *)malloc(sizeof(pthread_t) * num_threads);
  if (pool->threads == NULL) {
    ERROR("Ошибка выделения памяти для потоков");
    pthread_mutex_destroy(&pool->queue_mutex);
    pthread_cond_destroy(&pool->cond_nonempty);
    pthread_mutex_destroy(&pool->database_mutex);
    exit(EXIT_FAILURE);
  }

  for (int i = 0; i < num_threads; i++) {
    int create_result = pthread_create(&pool->threads[i], NULL,
                                       worker_thread_func, (void *)pool);
    if (create_result != 0) {
      ERROR("Ошибка инициализации потока");
      free(pool->threads);
      pthread_mutex_destroy(&pool->queue_mutex);
      pthread_cond_destroy(&pool->cond_nonempty);
      pthread_mutex_destroy(&pool->database_mutex);
      exit(EXIT_FAILURE);
    }
    pthread_detach(pool->threads[i]);
  }

  printf("Пул потоков успешно инициализирован с количеством потоков %d и "
         "очередью длиной %d\n",
         num_threads, max_queue_size);
  return 0;
}
