#ifndef TUPLE_SPACE_H
#define TUPLE_SPACE_H

#include <stdint.h>

#define TS_YES 1
#define TS_NO 0
#define TS_INT 0
#define TS_FLOAT 1
#define TS_SUCCESS 1
#define TS_FAILURE 0
#define TS_ID_SIZE 20

#pragma pack(1)
typedef struct
{
    uint8_t is_actual; /* does the data member contains data */
    uint8_t type;      /* what is the type of the data member */
    uint16_t padding;
    union
    {
        uint32_t int_field;
        float float_field;
    } data;
} field_t; /* a new type corresponding to one field of a tuple */
#pragma pack()

typedef struct
{
    char id[TS_ID_SIZE]; /* tuple name */
    uint8_t size;        /* how many fields does the tuple have */
    field_t *fields;
} Tuple;

/* API */
/* these functions return TS_SUCCESS or TS_FAILURE */
/* parameters: tuple name, other fields, no. of other fields */
int ts_out(char *id, field_t *fields, int size);
int ts_inp(char *id, field_t *fields, int size);
int ts_rdp(char *id, field_t *fields, int size);

#endif
