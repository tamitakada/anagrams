#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <string.h>
#include <netdb.h>
#include <errno.h>

#ifndef NETWORKING_H
#define NETWORKING_H

int server_setup();
void server_connect(int sd);
int client_connect();
void handle_client(int sd);

#endif
