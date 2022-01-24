#include "networking.h"

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
	
		//adding the first vowel
    int r = rand() % 5;
    chars[i] = vowels[r];
    
    //removing the first vowel from the list of avail vowels to prevent from duplicating
    char * vowels_left = malloc(sizeof(char) * 5);
  	chars[5] = '\0';
  	
  	//useful later for letter gen improvement
  	char * vowels_used = malloc(sizeof(char) * 3);
  	chars[3] = '\0';
  	
    int j;
    for (j = 0; j < 4; j++) {
    	if (j != r) {
    		vowels_left[j] = vowels[j];
    	}
    	vowels_used[0] = vowels[j];
    }
    
    //adding the second vowel; not that practical but only 2 vowels anyways
    r = rand() % 4;
    chars[i] = vowels_left[r];
    vowels_used[1] = vowels_left[r];
  }
  
  //adding the consonants 
  char bad_consonants[5] = {'z', 'x', 'j', 'q'};
  for (i = 2; i < 6; i++) {
  	char r = rand() % 26 + 97;
  	
  	//checking duplicates and vowels; if true, regenerate 
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

int get_word_points(char * word) {
  int fd = open("words.txt", O_RDONLY, 0644);

  char c;
  char w[7];
  int i = 0;
  while (read(fd, &c, sizeof(c))) {
    if (c == '\n') {
      w[i] = '\0';
      if (strcmp(w, word) == 0) {
          close(fd);
          return ((int) strlen(w)) * 100;
      }
      i = 0;
    } else {
      w[i] = c;
      i++;
    }
  }

  close(fd);
  return 0;
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
