#ifndef MY_NETWORK__
#define MY_NETWORK__

#include <arpa/inet.h>
#include <netinet/in.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define SIZE_M 512
#define IP_SERV "127.0.0.1"
#define PORT_SERV 8888
#define PORT_CLIENT 7777

/**
 * @brief Создаёт и биндит сокет
 * @param port Порт на котором будет забинжен сокет
 * @param ip IP для сокета
 * @return файловый дискриптор сокета - успех, -1 - не получилось.
 */
int create_sock(uint16_t port, const char* ip);

/**
 * @brief Функция чтения сообщения
 * @param fd Файловый дискриптор сокета
 * @param buf Указатель на буффер
 * @param size Размер буфера
 * @param sock Структура сокета (передаётся для записи &)
 * @return количество прочитаных бит - успех, -1 - не получилось.
 */
int my_recv(int fd, char* buf, size_t size, struct sockaddr_in* sock);

/**
 * @brief Функция отправки сообщения
 * @param fd Файловый дискриптор сокета
 * @param buf Указатель на буффер
 * @param size Размер буфера
 * @param sock Структура сокета
 * @return 0 - успех, -1 - не получилось.
 */
int my_send(int fd, char* buf, size_t size, struct sockaddr_in sock);

/**
 * @brief Функция заполнения сокета
 * @param tmp Структура сокета (передаётся для записи &)
 * @param port Порт для сокета
 * @param ip IP для сокета
 * @return 0 - успех, -1 - не получилось.
 */
int fill_sockaddr(struct sockaddr_in* tmp, uint16_t port, const char* ip);

/**
 * @brief Удаляет сокет
 * @param fd Файловый дискриптор сокета
 */
void delete_sock(int fd);

#endif