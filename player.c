#include "networking.h"

void client_processing(int sd) {
  char msg[100];
  printf("Input: ");
  fgets(msg, sizeof(msg), stdin);
  
  write(sd, msg, sizeof(msg));

  char processed[100];
  int n = read(sd, processed, sizeof(processed));
  if (n) {
    printf("Processed: %s\n", processed);
    client_processing(sd);
  }
}

int main() {
  int sd = client_connect();
  client_processing(sd);
}
