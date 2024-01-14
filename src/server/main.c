#include <stdio.h>

#include "server.h"
#include "tuple_space.h"
#include "protocol.h"
#include <string.h>
#include <arpa/inet.h>

int main()
{
    int sockfd = initialize_socket();

    Tuple tuple;

    printf("Tuple space server listening on [UDP] port %d\n", PORT);
    char buffer[MAX_BUFF];


    while (1)
    {
        memset(buffer, 0, MAX_BUFF);

        handle_client(sockfd, buffer, MAX_BUFF);
        printf("Received: %s\n", buffer);

        uint8_t type = read_protocol_message(buffer, &tuple);

        printf("Type: %x\n", type);
        printf("Tuple id: %s\n", tuple.id);
        printf("Tuple size: %x\n", tuple.size);

        for (int i = 0; i < tuple.size; i++)
        {
            printf("Tuple is_actual %x\n", tuple.fields[i].is_actual);
            printf("Tuple type %x\n", tuple.fields[i].type);
            printf("Tuple field %d: %x\n", i, ntohl(tuple.fields[i].data.int_field));
        }
        printf("#######################################\n");
    }

    printf("Closing socket\n");

    close(sockfd);
    return 0;
}