#include "../include/my_network.h"

int my_send(int fd, char* buf, size_t size, struct sockaddr_in sock)
{
    if (buf == NULL || size > SIZE_M) {
        fprintf(stderr, "buf or size");
        return -1;
    }

    if ((sendto(fd, buf, size, 0, (struct sockaddr*)&sock, sizeof(sock)))
        == -1) {
        fprintf(stderr, "sendto");
        return -1;
    }

    return 0;
}
