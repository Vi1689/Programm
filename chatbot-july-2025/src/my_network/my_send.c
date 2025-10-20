#include "my_network/my_network.h"
#include <sodium.h>

int my_send(int fd, char *buf, size_t size, struct sockaddr_in sock) {

  unsigned char en_de_cryption[crypto_secretbox_KEYBYTES] = {
      0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef, 0xfe, 0xdc, 0xba,
      0x98, 0x76, 0x54, 0x32, 0x10, 0x00, 0x11, 0x22, 0x33, 0x44, 0x55,
      0x66, 0x77, 0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff};

  if (buf == NULL || size > 544) {
    ERROR("buf or size");
    return -1;
  }

  unsigned char tmp[544] = {'\000'};

  unsigned char nonce[crypto_secretbox_NONCEBYTES];
  unsigned char ciphertext[sizeof(tmp) + crypto_secretbox_MACBYTES -
                           crypto_secretbox_MACBYTES -
                           crypto_secretbox_NONCEBYTES];

  randombytes_buf(nonce, sizeof(nonce));

  if (crypto_secretbox_easy(ciphertext, (unsigned char *)buf,
                            sizeof(ciphertext) - crypto_secretbox_MACBYTES,
                            nonce, en_de_cryption) == -1) {
    ERROR("crypto_secretbox_easy");
  }

  memcpy(tmp, nonce, sizeof(nonce));
  memcpy(tmp + sizeof(nonce), ciphertext, sizeof(ciphertext));

  if ((sendto(fd, tmp, sizeof(tmp), 0, (struct sockaddr *)&sock,
              sizeof(sock))) == -1) {
    ERROR("sendto");
    return -1;
  }

  return 0;
}
