#include "../include/my_network.h"

int my_recv(int fd, char* buf, size_t size, struct sockaddr_in* sock)
{
    if (buf == NULL) {
        fprintf(stderr, "buf");
        return -1;
    }

    memset(buf, '\000', size);

    socklen_t len = sizeof(*sock);

    ssize_t read = 0;

    if ((read = recvfrom(fd, buf, size, 0, (struct sockaddr*)&(*sock), &len))
        == -1) {
        fprintf(stderr, "recvfrom");
        return -1;
    }

    return read;
}
