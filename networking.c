#include "networking.h"
#include <ctype.h>

int server_setup() {
  struct addrinfo * hints, * results;
  hints = calloc(1, sizeof(struct addrinfo));
  hints->ai_family = AF_INET;
  hints->ai_socktype = SOCK_STREAM;
  hints->ai_flags = AI_PASSIVE;
  getaddrinfo(NULL, "9845", hints, &results);

  int sd = socket(results->ai_family, results->ai_socktype, results->ai_protocol);

  bind(sd, results->ai_addr, results->ai_addrlen);

  free(hints);
  freeaddrinfo(results);

  return sd;
}

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
  for (i = 0; i < 6; i++) {
    if (i < 2) {
        char vowels[5] = {'a', 'e', 'i', 'o', 'u'};
        int r = rand() % 5;
        chars[i] = vowels[r];
    } else {
      char r = rand() % 26 + 97;
      while (is_duplicate(chars, r)) {
        r = rand() % 26 + 97;
      }
      chars[i] = r;
    }
  }
  return chars;
}

void processing(int sd) {
  char * chars = generate_characters();

  write(sd, chars, sizeof(chars));

  while (1) {
    char word[6];
    read(sd, word, sizeof(word));
    printf("%s\n", word);
  }

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
  int fd = open("words.txt");

  char c;
  char w[7];
  int i = 0;
  while (read(fd, &c, sizeof(c))) {
    if (c == '\n') {
      w[i] = '\0';
      if (strcmp(w, word) == 0) return strlen(word) * 100;
      i = 0;
    } else {
      w[i] = c;
      i++;
    }
  }

  return 0;
}

void handle_client(int sd) {
    int pipe[2];
    pipe(pipe);

    int client_socket;
    socklen_t sock_size;
    struct sockaddr_storage client_address;
    sock_size = sizeof(client_address);
    client_socket = accept(sd,(struct sockaddr *)&client_address, &sock_size);

    printf("Accepted match!\n");

    int f = fork();
    if (f) {
        close(pipe[1]);
        processing(client_socket);
    } else {
        close(pipe[0]);
        while (1) {
          char * word = get_input();
          int pts = get_word_points(word);
          printf("%d\n", pts);
          // sth
        }
    }
}

void server_connect(int sd) {
  listen(sd, 10);
  printf("Listening for clients...\n");
  handle_client(sd);
}

int client_connect() {
  struct addrinfo * hints, * results;
  hints = calloc(1,sizeof(struct addrinfo));
  hints->ai_family = AF_INET;
  hints->ai_socktype = SOCK_STREAM;
  getaddrinfo("127.0.0.1", "9845", hints, &results);

  int sd = socket(results->ai_family, results->ai_socktype, results->ai_protocol);

  connect(sd, results->ai_addr, results->ai_addrlen);
  printf("Connected to server!\n");

  free(hints);
  freeaddrinfo(results);

  return sd;
}
