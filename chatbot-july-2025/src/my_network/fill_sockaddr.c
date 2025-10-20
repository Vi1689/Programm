#include "my_network/my_network.h"

int fill_sockaddr(struct sockaddr_in *tmp, uint16_t port, const char *ip) {

  memset(tmp, 0, sizeof(*tmp));

  (*tmp).sin_family = AF_INET;
  (*tmp).sin_port = htons(port);
  if (inet_aton(ip, &(*tmp).sin_addr) == 0) {
    ERROR("inet_aton");
    return -1;
  }

  return 0;
}