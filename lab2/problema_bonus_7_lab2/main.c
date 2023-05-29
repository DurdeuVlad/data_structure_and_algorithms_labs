#include <stdio.h>
#include <stdlib.h>

// *Scrieti un program pentru a inversa o lista simplu
// inlantuita in mod eficient (timp 0(n) si spatiu aditional O(1)).
// Lista este implementata folosind pointer la first.
// Pentru lista:

typedef struct nod{
    int key;
    struct nod* next;
}NodeT;

NodeT* create(int givenkey){
    NodeT * node = malloc(sizeof(NodeT));
    node->key=givenkey;
    node->next=NULL;
    return node;
}

//afisare
void afisare(NodeT* first){
    NodeT * p = first;
    while(p){
        printf("%d->", p->key);
        p = p->next;
    }
    printf("NULL\n");
}

//insert_first
void insert_first(NodeT** first, int givenkey){
    // lista este goala
    if(*first == NULL){
        *first = create(givenkey);
    }
    // lista contine un sigur element
    // lista este generala cel putin 2 elemente
    else {
        NodeT * p = create(givenkey);
        p->next = *first;
        *first = p;
    }

}

void invert_list(NodeT** first){
    if(*first == NULL)return;
    NodeT* one = *first, * two, * three;

    two = (*first)->next;
    if(two == NULL)return;
    three = two->next;

    while(three != NULL){
        two->next = one;
        one = two;
        two = three;
        three = three->next;
    };
    two->next = one;
    (*first)->next=NULL;
    *first=two;

}

int main()
{
    NodeT* first = NULL;
    insert_first(&first, 1);
    insert_first(&first, 2);
    insert_first(&first, 3);
    insert_first(&first, 4);
    insert_first(&first, 5);
    afisare(first);
    invert_list(&first);
    afisare(first);

    return 0;
}
