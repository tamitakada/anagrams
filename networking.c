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

void processing(int sd) {
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
    
    printf("Accepted client!\n");
    
    int pid = fork();
    if (pid > 0) {
      handle_client(sd);
    } else {
      printf("Forked!\n");
      processing(client_socket);
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

