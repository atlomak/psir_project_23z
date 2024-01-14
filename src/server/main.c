#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>

#include "server.h"
#include "tuple_space.h"
#include "protocol.h"
#include "tuples_linked_list.h"

int main()
{
    int sockfd = initialize_socket();

    printf("Tuple space server listening on [UDP] port %d\n", PORT);
    char buffer[MAX_BUFF];

    printf("Initialize tuple space linked list");
    Linked_list *list = create_linked_list();
    

    while (1)
    {
        memset(buffer, 0, MAX_BUFF);

        struct sockaddr_in client_addr;
        handle_client(sockfd, buffer, MAX_BUFF, &client_addr);

        Tuple tuple;

        switch (read_protocol_message(buffer, &tuple))
        {
        case REQUEST_INP:

            printf("REQUEST INP\n");
            printf("Tuple id: %s\n", tuple.id);
            printf("Tuple size: %x\n", tuple.size);

            break;
        case REQUEST_RD:

            printf("REQUEST RD\n");
            printf("Tuple id: %s\n", tuple.id);
            printf("Tuple size: %x\n", tuple.size);

            break;
        case REQUEST_OUT:

            printf("REQUEST OUT\n");
            printf("Tuple id: %s\n", tuple.id);
            printf("Tuple size: %x\n", tuple.size);

            add_tuple(list, &tuple);

            break;
        default:
            break;
        }
    }

    printf("Closing socket\n");

    close(sockfd);
    return 0;
}