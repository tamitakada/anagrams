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
  while (arr) {
    if (*arr == c) return 1;
    arr++;
  }
  return 0;
}

char * generate_characters() {
  printf("gen");
  char * chars = malloc(sizeof(char) * 6);
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
  int i;
  for (i = 0; i < 6; i++) {
    printf("%c\n", chars[i]);
  }

    char msg[100];
    int n = read(sd, msg, sizeof(msg));
    if (n) {
        int i = 0;
        while (msg[i]) {
            msg[i] = toupper(msg[i]);
            i++;
        }

        write(sd, msg, sizeof(msg));
        processing(sd);
    }
}

void handle_client(int sd) {
    int client_socket;
    socklen_t sock_size;
    struct sockaddr_storage client_address;
    sock_size = sizeof(client_address);
    client_socket = accept(sd,(struct sockaddr *)&client_address, &sock_size);

    printf("Accepted match!\n");

    processing(client_socket);
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
