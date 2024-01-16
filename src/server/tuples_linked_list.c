#include "tuples_linked_list.h"
#include "tuple_space.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int _compare_tuples(Tuple *filer_tuple, Tuple *tuple);
int _compare_fields(field_t *filter_field, field_t *field);

Linked_list *create_linked_list()
{
    Linked_list *list = malloc(sizeof(Linked_list));
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return list;
}

/*
    Function to add tuple to linked list.
    If tuple added return list size after append (index).
*/
int add_tuple(Linked_list *list, Tuple *tuple)
{
    struct Node *node = malloc(sizeof(struct Node));

    Tuple *p_tuple = malloc(sizeof(p_tuple));

    p_tuple->size = tuple->size;
    strncpy(p_tuple->id, tuple->id, TS_ID_SIZE);

    field_t *p_fields = malloc(sizeof(field_t) * tuple->size);
    memcpy(p_fields, tuple->fields, sizeof(field_t) * tuple->size);

    p_tuple->fields = p_fields;

    node->tuple = p_tuple;
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
    return list->size;
}

/*
    Function to remove tuple from linked list.
    Before remove tuple is copied to a passed tuple.
    If tuple removed return 0, else -1.
*/
int remove_tuple(Linked_list *list, Tuple *tuple)
{
    struct Node *prev = NULL;
    struct Node *curr = list->head;

    while (curr != NULL)
    {
        if (_compare_tuples(curr->tuple, tuple) == 0)
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

            /* copy from list to tuple before remove from list */
            free(tuple->fields);

            tuple->fields = malloc(sizeof(field_t) * tuple->size);
            memcpy(tuple->fields, curr->tuple->fields, sizeof(field_t) * tuple->size);

            /* remove from list */
            free(curr->tuple);
            free(curr);
            list->size--;
            return list->size;
        }

        prev = curr;
        curr = curr->next;
    }
    return -1;
}

/*
    Function to get tuple from linked list.
    If tuple found return index, else -1.
*/
int get_tuple(Linked_list *list, Tuple *tuple)
{
    int index = 0;
    struct Node *curr = list->head;

    while (curr != NULL)
    {
        if (_compare_tuples(tuple, curr->tuple) == 0)
        {
            free(tuple->fields);

            tuple->fields = malloc(sizeof(field_t) * tuple->size);
            memcpy(tuple->fields, curr->tuple->fields, sizeof(field_t) * tuple->size);
            return index;
        }
        curr = curr->next;
        index++;
    }
    return -1;
}

/*
    Helper function, to compare tuple.
    Function is using tuple as filter.
    If match found return 0.
    If same id but no match return 1, else 2.
*/
int _compare_tuples(Tuple *filer_tuple, Tuple *tuple)
{
    if (strncmp(filer_tuple->id, tuple->id, TS_ID_SIZE))
    {
        return 2;
    }

    if (filer_tuple->size != tuple->size)
    {
        return 1;
    }

    for (int i = 0; i < filer_tuple->size; i++)
    {
        if (_compare_fields(&filer_tuple->fields[i], &tuple->fields[i]))
        {
            return 1;
        }
    }
    return 0;
}

/*
    Helper function to comapre field_t.
    field_t is equal when:
    both have the same data type and data value;
    filters is_actual=TS_NO and both have the same data type.
*/
int _compare_fields(field_t *filter_field, field_t *field)
{
    if (filter_field->type != field->type)
    {
        return 1;
    }

    /* datatype doesnt matter when comparing bits, using int */
    if ((filter_field->is_actual == TS_YES) && (filter_field->data.int_field != field->data.int_field))
    {
        return 1;
    }
    return 0;
}