#include "networking.h"

int main() {
  int sd = client_connect();
  client_processing(sd);
}
