#include <client/client.h>

int main() {

  if (start_client(CLIENT_PORT, "0.0.0.0") == -1) {
    return -1;
  }

  return 0;
}