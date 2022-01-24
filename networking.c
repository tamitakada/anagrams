#include "networking.h"
#include "word_handling.h"
#include "game.h"

struct player_data {
  int server_pid;
  int server_socket;
};

// Global vars
struct player_data players[2];

// Signal handler
void server_end_game(int sig) {
  if (sig == SIGALRM) {
    int i;
    for (i = 0; i < 2; i++) kill(players[i].server_pid, SIGTERM);
    exit(0);
  } else if (sig == SIGTERM) {
    int winner = 1;

    int score_0 = score_handling("score_0.data");
    int score_1 = score_handling("score_1.data");

    if (score_0 > score_1) winner = 0;
    else if (score_0 == score_1) winner = -1;

    int i;
    for (i = 0; i < 2; i++) {
      int num = -1;
      write(players[i].server_socket, &num, sizeof(int));

      int sd = players[i].server_socket;
      if (winner == i) {
        char msg[20] = "You lose :(";
        write(sd, msg, strlen(msg) * sizeof(char));
      } else if (winner < 0) {
        char msg[20] = "It's a tie!";
        write(sd, msg, strlen(msg) * sizeof(char));
      } else {
        char msg[20] = "You win!";
        write(sd, msg, strlen(msg) * sizeof(char));
      }
    }

    exit(0);
  }
}

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

/*
  processing - Gets words inputted by the player and assigns points

  Takes the following parameters:
    int player_number - Index of player for accessing data in struct
    char * chars - The set characters that can be used in the game
*/
void processing(int player_number, char * chars) {
  int sd = players[player_number].server_socket;

  // Word history file
  char * filename;
  char * score_filename;
  if (player_number) {
    filename = "player_1.txt";
    score_filename = "score_0.data";
  } else {
    filename = "player_0.txt";
    score_filename = "score_1.data";
  }

  int fd = open(filename, O_CREAT, 0644);
  close(fd);

  fd = open(score_filename, O_CREAT | O_WRONLY, 0644);
  int def = 0;
  write(fd, &def, sizeof(int));
  close(fd);

  write(sd, chars, sizeof(chars));

  char word[7];
  int b;
  while (1) {
    b = read(sd, word, sizeof(word));
    word[b] = 0;
    printf("Received word: %s\n", word);
    
    int wd_pts;
    if (already_used(filename, word) || !is_in_char_set(word, chars)) wd_pts = 0;
    else wd_pts = get_word_points(word);

    fd = open(score_filename, O_RDWR, 0644);
    int current_pts;
    read(fd, &current_pts, sizeof(int));

    lseek(fd, 0, SEEK_SET);
    int new_pts = current_pts + wd_pts;
    write(fd, &new_pts, sizeof(int));
    close(fd);

    if (wd_pts) {
      word[b] = '\n';
      fd = open(filename, O_WRONLY | O_APPEND, 0644);
      write(fd, word, (b + 1) * sizeof(char));
      close(fd);
    }
    
    write(sd, &wd_pts, sizeof(int));
  }
}

void handle_client(int sd) {
  int number_clients = 0;
  while (number_clients < 2) {
    int client_socket;
    socklen_t sock_size;
    struct sockaddr_storage client_address;
    sock_size = sizeof(client_address);
    client_socket = accept(sd,(struct sockaddr *)&client_address, &sock_size);

    struct player_data player;
    player.server_socket = client_socket;
    players[number_clients] = player;
    
    printf("Player #%d joined!\n", number_clients);
    number_clients++;
  }
  
  char * chars = generate_characters();

  signal(SIGALRM, server_end_game);

  int pid_player_0 = fork();
  if (pid_player_0 > 0) {
    players[0].server_pid = pid_player_0;

    int pid_player_1 = fork();
    if (pid_player_1 > 0) {
      players[1].server_pid = pid_player_1;
      alarm(20);
      wait(NULL);
    } else {
      printf("Forked player #1!\n");
      // Set sig handler for forked server
      signal(SIGTERM, server_end_game);

      processing(1, chars);
    }
  } else {
    printf("Forked player #0!\n");
    // Set sig handler for forked server
    signal(SIGTERM, server_end_game);

    processing(0, chars);
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
