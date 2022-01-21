#include "networking.h"

void client_processing(int sd) {
  char letters[7];
  int n = read(sd, letters, sizeof(letters));
  if (n) {
    printf("Letters: %s\n", letters);
    // client_processing(sd);
  }

  while (1) {
    char * word = get_input();
    write(sd, word, (i + 1) * sizeof(char));
  }
}

int main() {
  int sd = client_connect();
  client_processing(sd);
}
