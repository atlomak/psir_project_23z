#include "protocol.h"
#include <stdlib.h>
#include <stdio.h>
#include <memory.h>

/*
Read tuple from received protocol message.
Returns type of message or -1 if error.
*/
int read_protocol_message(char *buffer, Tuple* tuple)
{
    protocol *p = (protocol *)buffer;
    p->id[TS_ID_SIZE - 1] = '\0';

    if ((unsigned long)(p->size) * sizeof(field_t) > MAX_BUFF)
    {
        printf("ERROR: Size to big.");
        return -1;
    }

    tuple->size = p->size;
    memcpy(tuple->id, p->id, TS_ID_SIZE);

    tuple->fields = malloc(sizeof(field_t) * tuple->size);
    memcpy(tuple->fields, p->fields, sizeof(field_t) * tuple->size);

    return p->type;
}