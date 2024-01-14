#ifndef SERVER_H
#define SERVER_H

#define BUFFER_SIZE 1024
#define PORT 8080

int initialize_socket();
void handle_client(int sockfd, char *buffer, int size);
void error(const char *msg);

#endif