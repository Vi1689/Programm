#include "my_network/my_network.h"
#include <sodium.h>

int my_recv(int fd, char *buf, size_t size, struct sockaddr_in *sock) {

  unsigned char en_de_cryption[crypto_secretbox_KEYBYTES] = {
      0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef, 0xfe, 0xdc, 0xba,
      0x98, 0x76, 0x54, 0x32, 0x10, 0x00, 0x11, 0x22, 0x33, 0x44, 0x55,
      0x66, 0x77, 0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff};

  if (buf == NULL) {
    ERROR("buf");
    return -1;
  }

  memset(buf, '\000', size);

  socklen_t len = sizeof(*sock);

  ssize_t read = 0;

  unsigned char tmp[544] = {'\000'};

  if ((read = recvfrom(fd, tmp, sizeof(tmp), 0, (struct sockaddr *)&(*sock),
                       &len)) == -1) {
    ERROR("recvfrom");
    return -1;
  }

  unsigned char nonce[crypto_secretbox_NONCEBYTES];
  unsigned char ciphertext[sizeof(tmp) + crypto_secretbox_MACBYTES -
                           crypto_secretbox_MACBYTES -
                           crypto_secretbox_NONCEBYTES];

  memcpy(nonce, tmp, sizeof(nonce));
  memcpy(ciphertext, tmp + sizeof(nonce), sizeof(ciphertext));

  if (crypto_secretbox_open_easy((unsigned char *)buf, ciphertext,
                                 sizeof(ciphertext), nonce,
                                 en_de_cryption) != 0) {
    ERROR("crypto_secretbox_open_easy");
    return -1;
  }

  return read;
}
