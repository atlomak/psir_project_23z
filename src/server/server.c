#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "server.h"
#include "protocol.h"

void error(const char *msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}

int initialize_socket()
{
    int sockfd;
    struct sockaddr_in server_addr;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0)
    {
        error("Socket creation failed");
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(sockfd, (const struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        error("Bind failed");
    }

    return sockfd;
}

void handle_client(int sockfd, char *buffer, int size, struct sockaddr_in *client_addr)
{
    socklen_t addr_size;
    int n;

    addr_size = sizeof(&client_addr);
    n = recvfrom(sockfd, buffer, size, 0, (struct sockaddr *)client_addr, &addr_size);
    if (n < 0)
    {
        error("Receive failed");
    }
    printf("Received message from %s:%d\n", inet_ntoa(client_addr->sin_addr), ntohs(client_addr->sin_port));
    printf("Buffer: %s\n", buffer);
}