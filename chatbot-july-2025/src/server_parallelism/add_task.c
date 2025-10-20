#include "error_handler.h"
#include "parallelism.h"
#include <stdlib.h>
#include <string.h>

int thread_pool_add_task(struct thread_pool *pool, const char *data,
                         ssize_t data_len,
                         const struct sockaddr_in *client_addr,
                         socklen_t client_addr_len) {
  if (pool == NULL || data == NULL || client_addr == NULL || data_len <= 0) {
    ERROR("thread_pool_add_task: Недопустимые аргументы.");
    return -1;
  }

  struct task *new_task = (struct task *)malloc(sizeof(struct task));
  if (new_task == NULL) {
    ERROR("thread_pool_add_task: Ошибка выделения памяти для задачи.");
    return -1;
  }

  if (data_len > MAX_UDP_PACKET_SIZE) {
    data_len = MAX_UDP_PACKET_SIZE;
    ERROR(
        "thread_pool_add_task: Полученный пакет UDP слишком большой, усечён.");
  }
  memcpy(new_task->data_buffer, data, data_len);
  new_task->data_len = data_len;
  memcpy(&new_task->client_addr, client_addr, client_addr_len);
  new_task->client_addr_len = client_addr_len;
  new_task->next = NULL;

  pthread_mutex_lock(&pool->queue_mutex);

  if (pool->task_queue_size >= pool->max_queue_size) {
    ERROR(
        "thread_pool_add_task: Очередь задач переполнена. UDP-пакет отброшен.");
    free(new_task);
    pthread_mutex_unlock(&pool->queue_mutex);
    return -1;
  }

  if (pool->task_queue_tail == NULL) {
    pool->task_queue_head = new_task;
    pool->task_queue_tail = new_task;
  } else {
    pool->task_queue_tail->next = new_task;
    pool->task_queue_tail = new_task;
  }
  pool->task_queue_size++;

  pthread_cond_signal(&pool->cond_nonempty);

  pthread_mutex_unlock(&pool->queue_mutex);
  return 0;
}