#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int key;
    struct node * link;
}Node;



Node* xor(Node *first, Node *last){
    uintptr_t first_safe = (uintptr_t) first;
    uintptr_t last_safe = (uintptr_t) last;
    return (Node*) (first_safe^last_safe);
}

Node* create(int key){
    Node * newNode = malloc(sizeof(Node));
    newNode->key=key;
    newNode->link=NULL;
    return newNode;
}

void afisare(Node * first){
    Node* current = first, *previous = NULL, *next = NULL;
    while(current!=NULL){
        printf("%d ", current->key);
        next = xor(previous, current->link);
        previous = current;
        current = next;

    }
}

void insert_first(Node**first, int key){
    Node * newNode = create(key);
    if(*first==NULL){
        *first = newNode;
        return;
    }
    newNode->link = xor(*first,NULL);
    *first = newNode;
}

void insert_last(Node**first, int key){
    Node * newNode = create(key);
    if(*first==NULL){
        *first = newNode;
        return;
    }

    Node* current = *first, *previous = NULL, *next = NULL;
    while(current!=NULL){
        next = xor(previous, current->link);
        previous = current;
        current = next;

    }
    newNode->link = xor(previous, NULL);
    previous->link = xor(previous->link, newNode);


}

int main()
{
    Node * first=NULL;
     //test insert_first
    insert_first(&first, 0);
    insert_first(&first, 1);
    insert_first(&first, 2);

    afisare(first);
     //test insert last;
    insert_last(&first, 3);
    insert_last(&first, 4);
    insert_last(&first, 5);

    afisare(first);

    return 0;
}
