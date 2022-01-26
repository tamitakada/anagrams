#include "networking.h"
#include "word_handling.h"

/*
  score_handling - Reads and returns score for current game
*/
int score_handling(char * game_score_file) {
  int score;
  int fd = open(game_score_file, O_RDONLY, 0644);
  read(fd, &score, sizeof(int));
  close(fd);

  return score;
}

void client_processing(int sd) {
  char letters[7];
  int n = read(sd, letters, sizeof(letters));
  int wd_pts = 0;
  while (1) {
    printf("Letters: %s\n", letters);
    printf("Points: %d\nInput: ", wd_pts);
    char * word = get_input();
    write(sd, word, strlen(word) * sizeof(char));
    int b = read(sd, &wd_pts, sizeof(int));
    while (b < sizeof(int)) {
      lseek(sd, -(b), SEEK_CUR);
      b = read(sd, &wd_pts, sizeof(int));
    }

    if (wd_pts < 0) break;
    else printf("+%d points\n\n", wd_pts);
  }
}