#include "list.h"

node_t *create_new_node(int x, int y)
{
    node_t *n = malloc(sizeof(node_t));
    n->x = x;
    n->y = y;
    n->next = NULL;
    return n;
}

node_t *insert_at_head(node_t **head, node_t *node_to_insert)
{
    node_to_insert->next = *head;
    *head = node_to_insert;
    return node_to_insert;
}
