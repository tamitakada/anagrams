#include "networking.h"
#include "word_handling.h"

/*
  score_handling - Reads and returns score for current game and sets high score
*/
int score_handling(char * game_score_file, char * high_score_file) {
  int score;
  int fd = open(game_score_file, O_RDONLY, 0644);
  read(fd, &score, sizeof(int));
  close(fd);

  //high score
  fd = open(high_score_file, O_CREAT | O_RDWR, 0644);
  int highscore;
  read(fd, &highscore, sizeof(int));
  if (highscore < score) write(fd, &score, sizeof(int));
  close(fd);

  return score;
}

void client_processing(int sd) {
  char letters[7];
  int n = read(sd, letters, sizeof(letters));
  if (n) printf("Letters: %s\n", letters);

  while (1) {
    char * word = get_input();
    write(sd, word, strlen(word) * sizeof(char));
    int wd_pts;
    int b = read(sd, &wd_pts, sizeof(int));
    while (b < sizeof(int)) {
      lseek(sd, -(b), SEEK_CUR);
      b = read(sd, &wd_pts, sizeof(int));
    }

    if (wd_pts < 0) break;
    else printf("+%d points\n\n", wd_pts);
  }
}

void show_high_scores() {
    int fd = open("p0_highscore", O_RDONLY, 0644);
    int highscore_0;
    read(fd, &highscore_0, sizeof(int));
    close(fd);

    fd = open("p1_highscore", O_RDONLY, 0644);
    int highscore_1;
    read(fd, &highscore_1, sizeof(int));
    close(fd);

    printf("High score for player #0: %d\n", highscore_0);
    printf("High score for player #1: %d\n", highscore_1);
}