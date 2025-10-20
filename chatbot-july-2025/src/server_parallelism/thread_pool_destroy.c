#include "error_handler.h"
#include "parallelism.h"

int thread_pool_destroy(struct thread_pool *pool) {
  if (pool == NULL) {
    ERROR("Пул не может быть пустым для уничтожения.");
    return -1;
  }

  pthread_mutex_lock(&pool->queue_mutex);
  pool->stop_pool = true;
  pthread_cond_broadcast(&pool->cond_nonempty);
  pthread_mutex_unlock(&pool->queue_mutex);

  free(pool->threads);

  struct task *current_task = pool->task_queue_head;
  while (current_task != NULL) {
    struct task *temp = current_task;
    current_task = current_task->next;
    free(temp);
  }
  pool->task_queue_head = NULL;
  pool->task_queue_tail = NULL;
  pool->task_queue_size = 0;

  pthread_mutex_destroy(&pool->queue_mutex);
  pthread_cond_destroy(&pool->cond_nonempty);
  pthread_mutex_destroy(&pool->database_mutex);

  printf("Пул потоков успешно уничтожен.\n");
  return 0;
}