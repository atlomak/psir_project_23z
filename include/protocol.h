#ifndef MYPROT_H
#define MYPROT_H

#include <stdint.h>
#include "tuple_space.h"

#define MAX_BUFF sizeof(protocol) + 10 * sizeof(field_t)
#define MAX_MSG_SIZE 20

#define HELLO_MSG "HELLO"
#define CLIENT_DATA_MSG "CDATA"
#define SERVER_DATA_MSG "SDATA"

#pragma pack(1)
typedef struct
{
    uint8_t type;
    char id[TS_ID_SIZE];
    uint8_t size;
    uint8_t fields[1];
} protocol;
#pragma pack()

int read_protocol_message(char *buffer, Tuple *tuple);

#endif