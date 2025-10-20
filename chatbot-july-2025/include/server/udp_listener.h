#ifndef UDP_LISTENER_H
#define UDP_LISTENER_H

#include <stddef.h>     // Для ssize_t
#include <sys/socket.h> // Для sockaddr

/**
 * @brief Функция, выполняемая отдельным потоком для прослушивания UDP-сокета.
 * Этот поток будет принимать все входящие UDP-пакеты и добавлять их в пул
 * задач.
 *
 * @param arg Указатель на аргументы потока (не используется, если g_thread_pool
 * глобален).
 * @return NULL.
 */
void *udp_listener_thread_func();

#endif
