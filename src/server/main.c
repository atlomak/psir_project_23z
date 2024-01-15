#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>

#include "server.h"
#include "tuple_space.h"
#include "protocol.h"
#include "tuples_linked_list.h"
#include "logging.h"

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

            if (remove_tuple(list, &tuple) >= 0)
            {
                printf("Tuple removed\n");
                send_tuple(&client_addr, sockfd, &tuple);
            }
            else
            {
                printf("Tuple not found\n");
                tuple.size = 0;
                send_tuple(&client_addr, sockfd, &tuple);
            }

            break;
        case REQUEST_RD:

            printf("REQUEST RD\n");

            if (get_tuple(list, &tuple) >= 0)
            {
                printf("Tuple found\n");
                send_tuple(&client_addr, sockfd, &tuple);
            }
            else
            {
                printf("Tuple not found\n");
                tuple.size = 0;
                send_tuple(&client_addr, sockfd, &tuple);
            }

            break;
        case REQUEST_OUT:
            printf("REQUEST OUT\n");

            add_tuple(list, &tuple);
            send_ack(&client_addr, sockfd, tuple.id);

            break;
        default:
            printf("ERROR: Unknown message type\n");
            break;
        }

        LOG_TUPLE((&tuple));
        LOG_LIST(list);
        PART_LINE();
    }

    printf("Closing socket\n");

    close(sockfd);
    return 0;
}