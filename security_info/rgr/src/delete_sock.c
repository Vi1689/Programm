#include "../include/my_network.h"

void delete_sock(int fd)
{
    close(fd);
}
