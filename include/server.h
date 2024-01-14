#ifndef SERVER_H
#define SERVER_H

#define PORT 8080

int initialize_socket();
void handle_client(int sockfd, char *buffer, int size, struct sockaddr_in *client_addr);
void error(const char *msg);

#endif