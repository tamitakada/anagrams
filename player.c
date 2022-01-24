#include "networking.h"
#include "game.h"

int main() {
  int sd = client_connect();
  client_processing(sd);

  printf("Game over!\n");

  char current;
  while (read(sd, &current, sizeof(char))) {
    printf("%c", current);
  }
  
  printf("\n\n");

  show_high_scores();
}
