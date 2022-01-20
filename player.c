#include "networking.h"

void client_processing(int sd) {
  char letters[7];
  int n = read(sd, letters, sizeof(letters));
  if (n) {
    printf("Letters: %s\n", letters);
    // client_processing(sd);
  }

  while (1) {
    char word[100];
    printf("Input: ");
    fgets(word, sizeof(word), stdin);

    int i = strcspn(word, "\n");
    if (i > 6) i = 6;
    word[i] = '\0';

    write(sd, word, (i + 1) * sizeof(char));
  }
}

int main() {
  int sd = client_connect();
  client_processing(sd);
}
