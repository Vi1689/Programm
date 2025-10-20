#include "my_network/my_network.h"

int create_sock(uint16_t port, const char *ip) {

  struct sockaddr_in serv = {0};

  int fd = socket(AF_INET, SOCK_DGRAM, 0);
  if (fd == -1) {
    ERROR("socket");
    return -1;
  }

  if (fill_sockaddr(&serv, port, ip) == -1) {
    return -1;
  }

  if ((bind(fd, (struct sockaddr *)&serv, sizeof(serv))) == -1) {
    ERROR("bind");
    return -1;
  }

  return fd;
}
