#ifndef LINKED_LIST_H
#define LINKED_LIST_H
#include "tuple_space.h"

struct Node
{
    Tuple *tuple;
    struct Node *next;
};

typedef struct
{
    struct Node *head;
    struct Node *tail;
    int size;
} Linked_list;

Linked_list *create_linked_list();

void add_tuple(Linked_list *list, Tuple *tuple);

void remove_tuple(Linked_list *list, char *id);

#endif
