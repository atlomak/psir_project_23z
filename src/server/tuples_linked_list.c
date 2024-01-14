#include "tuples_linked_list.h"
#include "tuple_space.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


Linked_list *create_linked_list()
{
    Linked_list *list = malloc(sizeof(Linked_list));
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return list;
}

void add_tuple(Linked_list *list, Tuple *tuple)
{
    struct Node *node = malloc(sizeof(struct Node));
    node->tuple = tuple;
    node->next = NULL;

    if (list->head == NULL)
    {
        list->head = node;
        list->tail = node;
    }
    else
    {
        list->tail->next = node;
        list->tail = node;
    }

    list->size++;
}

void remove_tuple(Linked_list *list, char *id)
{
    struct Node *prev = NULL;
    struct Node *curr = list->head;

    while (curr != NULL)
    {
        if (strcmp(curr->tuple->id, id) == 0)
        {
            if (prev == NULL)
            {
                list->head = curr->next;
            }
            else
            {
                prev->next = curr->next;
            }

            if (curr->next == NULL)
            {
                list->tail = prev;
            }

            free(curr->tuple->fields);
            free(curr->tuple);
            free(curr);
            list->size--;
            return;
        }

        prev = curr;
        curr = curr->next;
    }
}