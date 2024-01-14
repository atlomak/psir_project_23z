#include "protocol.h"

#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <arpa/inet.h>
#include <netinet/in.h>

/*
Read tuple from received protocol message.
Returns type of message or -1 if error.
*/
int read_protocol_message(char *buffer, Tuple *tuple)
{
    protocol *p = (protocol *)buffer;
    p->id[TS_ID_SIZE - 1] = '\0';

    unsigned long _received_size = sizeof(protocol) + ((unsigned long)(p->size) * sizeof(field_t));

    if (_received_size > MAX_BUFF)
    {
        printf("ERROR: Size to big.\n");
        printf("Size: %ld\n", _received_size);
        printf("Max buffer size allowed: %ld\n", MAX_BUFF);
        return -1;
    }

    tuple->size = p->size;
    memcpy(tuple->id, p->id, TS_ID_SIZE);

    tuple->fields = malloc(sizeof(field_t) * tuple->size);
    memcpy(tuple->fields, p->fields, sizeof(field_t) * tuple->size);

    for (int i = 0; i < tuple->size; i++)
    {
        tuple->fields[i].data.int_field = ntohl(tuple->fields[i].data.int_field);
    }

    return p->type;
}

int send_ack(struct sockaddr_in *client_addr, int sockfd, char *id)
{
    protocol p;
    p.type = (uint8_t)ACK;
    p.size = 0;
    strncpy(p.id, id, TS_ID_SIZE);

    if (sendto(sockfd, &p, sizeof(protocol), 0, (struct sockaddr *)client_addr, sizeof(struct sockaddr_in)) < 0)
    {
        printf("ERROR: Could not send ACK.\n");
        return -1;
    }

    return 0;
}