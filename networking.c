#include "networking.h"
#include "word_handling.h"

int server_setup() {
  struct addrinfo * hints, * results;
  hints = calloc(1, sizeof(struct addrinfo));
  hints->ai_family = AF_INET;
  hints->ai_socktype = SOCK_STREAM;
  hints->ai_flags = AI_PASSIVE;
  getaddrinfo(NULL, "9846", hints, &results);

  int sd = socket(results->ai_family, results->ai_socktype, results->ai_protocol);

  bind(sd, results->ai_addr, results->ai_addrlen);

  free(hints);
  freeaddrinfo(results);

  return sd;
}

void processing(int sd, char * chars) {
    write(sd, chars, sizeof(chars));

    char word[7];
    int b;
    while (1) {
        b = read(sd, word, sizeof(word));
        word[b] = 0;
        printf("Received word: %s\n", word);
        int wd_pts = get_word_points(word);
        write(sd, &wd_pts, sizeof(int));
    }
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

    printf("+%d points\n\n", wd_pts);
  }
}

void handle_client(int sd) {
    int number_clients = 0;
    int client_sockets[2];
    while (number_clients < 2) {
        int client_socket;
        socklen_t sock_size;
        struct sockaddr_storage client_address;
        sock_size = sizeof(client_address);
        client_socket = accept(sd,(struct sockaddr *)&client_address, &sock_size);
        client_sockets[number_clients] = client_socket;
        
        printf("Player #%d joined!\n", number_clients);
        number_clients++;
    }
    
    char * chars = generate_characters();
    int pid_player_0 = fork();
    if (pid_player_0 > 0) {
        int pid_player_1 = fork();
        if (pid_player_1 == 0) {
            printf("Forked player #1!\n");
            processing(client_sockets[1], chars);
        }
    } else {
        printf("Forked player #0!\n");
        processing(client_sockets[0], chars);
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
  getaddrinfo("127.0.0.1", "9846", hints, &results);

  int sd = socket(results->ai_family, results->ai_socktype, results->ai_protocol);

  connect(sd, results->ai_addr, results->ai_addrlen);
  printf("Connected to server!\n");

  free(hints);
  freeaddrinfo(results);

  return sd;
}
