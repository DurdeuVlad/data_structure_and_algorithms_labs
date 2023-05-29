#include <stdio.h>
#include <stdlib.h>

typedef struct node_type
{
    KeyT key; /* optional */
    ValueT value;
    /* pointer to next node */
    struct node_type *next;
    /* pointer to previous node */
    struct node_type *prev;
} NodeDL;


int main()
{
    printf("Hello world!\n");
    return 0;
}
