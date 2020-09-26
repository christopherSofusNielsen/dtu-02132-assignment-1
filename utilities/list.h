#if !defined(_LIST_H__)
#define _LIST_H__

#include <stdlib.h>
#include <stdio.h>

struct node
{
    int x;
    int y;
    struct node *next;
};

typedef struct node node_t;

node_t *create_new_node(int x, int y);
node_t *insert_at_head(node_t **head, node_t *node_to_insert);

#endif // _LIST_H__
