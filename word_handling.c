#include "networking.h"
#include <math.h>

int is_duplicate(char * arr, char c) {
  while (*arr) {
    if (*arr == c) return 1;
    arr++;
  }
  return 0;
}

char * generate_characters() {
  char * chars = malloc(sizeof(char) * 7);
  chars[6] = '\0';

	int i;
  char vowels[5] = {'a', 'e', 'i', 'o', 'u'};
	
	//to generate the first 2 vowels without duplicating 
	for (i = 0; i < 2; i++) {
    int r = rand() % 5;
    char v = vowels[r];

    //reroll if duplicate
    while (is_duplicate(chars, v)) {
      int r = rand() % 5;
      char v = vowels[r];
    }
    chars[i] = v;
  }
  
  //adding the consonants 
  char bad_consonants[5] = {'z', 'x', 'j', 'q'};
  for (i = 2; i < 6; i++) {
  	char r = rand() % 26 + 97;
  	
  	//checking duplicates, vowels, and consonants; if true, regenerate 
    while (is_duplicate(chars, r) || is_duplicate(vowels, r) || is_duplicate(bad_consonants, r)) {
    	r = rand() % 26 + 97;
    }  
    
    //adding it to array
    chars[i] = r;
  }
  
  return chars;
}

char * get_input() {
  char word[100];
  printf("Input: ");
  fgets(word, sizeof(word), stdin);

  int i = strcspn(word, "\n");
  if (i > 6) i = 6;
  word[i] = '\0';

  char * to_return = malloc(sizeof(word));
  strcpy(to_return, word);

  return to_return;
}

int already_used(char * filename, char * word) {
  int fd = open(filename, O_RDONLY, 0644);

  char past_word[7];
  char current;
  int i = 0;
  while (read(fd, &current, sizeof(char))) {
    if (current == '\n') {
      past_word[i] = 0;
      i = 0;
      if (strcmp(past_word, word) == 0) {
        close(fd);
        return 1;
      }
    } else {
      past_word[i] = current;
      i++;
    }
  }

  close(fd);
  return 0;
}

int get_word_points(char * word) {
  // if already_used(filename, word) {
  //   printf("Word already used!\n");
  //   return 0;
  // }
  int fd = open("words.txt", O_RDONLY, 0644);
  FILE * fp = fopen("words.txt", "r");

  char w[7];
  while (fgets(w, sizeof(w), fp)) {
    w[strcspn(w, "\n")] = 0;
    printf("string: %s, %s\n", w, word);
    if (strcmp(w, word) == 0) {
      close(fd);
      double len = (double) strlen(w) - 1.0;
      return (int) pow(2.0, len) * 100;
    }
  }

  close(fd);
  return 0;
}
