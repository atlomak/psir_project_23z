#ifndef MYPROT_H
#define MYPROT_H

#include <stdint.h>
#include "tuple_space.h"

#define MAX_BUFF sizeof(protocol) + 20 * sizeof(field_t)

#define REQUEST_INP 0
#define REQUEST_RD 1
#define REQUEST_OUT 2

#define REPLY_INP 3
#define REPLY_DF 4
#define ACK 5

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