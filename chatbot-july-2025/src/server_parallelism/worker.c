#include "client/client.h"
#include "data_base.h"
#include "error_handler.h"
#include "my_analyzer.h"
#include "my_network.h"
#include "my_parse.h"
#include "parallelism.h"
#include <arpa/inet.h>
#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_STR_LEN (32 + 1)
#define MAX_PASSWORD_STR_LEN (32 + 1)

extern struct data_base *g_database;
extern int g_server_socket;

void *worker_thread_func(void *arg) {
  struct thread_pool *pool = (struct thread_pool *)arg;
  struct task *current_task = NULL;
  char response_buffer[MAX_UDP_PACKET_SIZE];
  char output_buffer[MAX_UDP_PACKET_SIZE];

  while (true) {
    pthread_mutex_lock(&pool->queue_mutex);

    while (pool->task_queue_head == NULL && !pool->stop_pool) {
      pthread_cond_wait(&pool->cond_nonempty, &pool->queue_mutex);
    }

    if (pool->stop_pool && pool->task_queue_head == NULL) {
      pthread_mutex_unlock(&pool->queue_mutex);
      break;
    }

    current_task = pool->task_queue_head;
    pool->task_queue_head = current_task->next;
    if (pool->task_queue_head == NULL) {
      pool->task_queue_tail = NULL;
    }
    pool->task_queue_size--;

    pthread_mutex_unlock(&pool->queue_mutex);

    if (current_task != NULL) {
      struct client_message *received_client_message =
          (struct client_message *)current_task->data_buffer;

      printf("Поток %lu: Обработка данных от %s:%d: Логин=\"%s\", "
             "Сообщение=\"%s\"\n",
             pthread_self(), inet_ntoa(current_task->client_addr.sin_addr),
             ntohs(current_task->client_addr.sin_port),
             received_client_message->user_login,
             received_client_message->message);

      struct client current_client_info;
      memset(&current_client_info, 0, sizeof(struct client));

      current_client_info.username = (char *)malloc(MAX_USERNAME_STR_LEN);
      if (current_client_info.username == NULL) {
        ERROR("Ошибка выделения памяти для username");
        free(current_task);
        continue;
      }

      current_client_info.user_password = (char *)malloc(MAX_PASSWORD_STR_LEN);
      if (current_client_info.user_password == NULL) {
        ERROR("Ошибка выделения памяти для user_password");
        free(current_client_info.username);
        free(current_task);
        continue;
      }

      memset(current_client_info.username, 0, MAX_USERNAME_STR_LEN);
      memset(current_client_info.user_password, 0, MAX_PASSWORD_STR_LEN);

      strncpy(current_client_info.username, received_client_message->user_login,
              MAX_USERNAME_STR_LEN - 1);
      current_client_info.username[MAX_USERNAME_STR_LEN - 1] = '\0';

      current_client_info.user_ip_address = current_task->client_addr.sin_addr;

      memset(response_buffer, 0, sizeof(response_buffer));
      int type = 0;

      pthread_mutex_lock(&pool->database_mutex);

      int analyz_result = analyzer(
          g_database, &current_client_info, received_client_message->message,
          response_buffer, sizeof(response_buffer), &type);

      if (analyz_result != 0) {
        ERROR("Не удалось проанализировать сообщение.");
        printf("Поток %lu: Ошибка анализа сообщения от %s:%d.\n",
               pthread_self(), inet_ntoa(current_task->client_addr.sin_addr),
               ntohs(current_task->client_addr.sin_port));

        pthread_mutex_unlock(&pool->database_mutex);
        struct sockaddr_in dest_addr_error;
        memset(&dest_addr_error, 0, sizeof(dest_addr_error));
        dest_addr_error.sin_family = AF_INET;
        dest_addr_error.sin_port = current_task->client_addr.sin_port;
        dest_addr_error.sin_addr = current_task->client_addr.sin_addr;

        my_send(g_server_socket, "ERROR: Unable to process your request.",
                strlen("ERROR: Unable to process your request."),
                dest_addr_error);
      } else {
        int parse_result =
            operation(type, output_buffer, sizeof(output_buffer), g_database,
                      &current_client_info, response_buffer);
        if (parse_result != 0) {
          ERROR("Операция с базой данных завершилась неудачно.");
          printf("Поток %lu: Ошибка операции с БД для %s:%d. Код: %d\n",
                 pthread_self(), inet_ntoa(current_task->client_addr.sin_addr),
                 ntohs(current_task->client_addr.sin_port), parse_result);

          pthread_mutex_unlock(&pool->database_mutex);
          struct sockaddr_in dest_addr_db_error;
          memset(&dest_addr_db_error, 0, sizeof(dest_addr_db_error));
          dest_addr_db_error.sin_family = AF_INET;
          dest_addr_db_error.sin_port = current_task->client_addr.sin_port;
          dest_addr_db_error.sin_addr = current_client_info.user_ip_address;

          my_send(g_server_socket, "ERROR: Database operation failed.",
                  strlen("ERROR: Database operation failed."),
                  dest_addr_db_error);
        } else {
          pthread_mutex_unlock(&pool->database_mutex);

          my_send(g_server_socket, output_buffer, strlen(output_buffer),
                  current_task->client_addr);

          if (type == COME || type == UPDATA) {
            pthread_mutex_lock(&pool->database_mutex);
            if (send_history_mess(g_server_socket, current_task->client_addr,
                                  g_database, &current_client_info) == -1) {
              ERROR("send_history_mess");
            }
            pthread_mutex_unlock(&pool->database_mutex);
          }

          printf("Поток %lu: Отправлен ответ клиенту %s:%d: \"%s\"\n",
                 pthread_self(), inet_ntoa(current_task->client_addr.sin_addr),
                 ntohs(current_task->client_addr.sin_port), output_buffer);
        }
      }
      free(current_client_info.username);
      free(current_client_info.user_password);
      free(current_task);
    }
  }
  printf("Поток %lu: Завершение работы.\n", pthread_self());
  return NULL;
}
