#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int key;
    struct node* next;
}Node;

Node* create(int n){
    Node *p = malloc(sizeof(Node));
    p->key = n;
    p->next = NULL;
    return p;
}

void afisare(Node* first){
    while(first!=NULL){
        printf("%d ", first->key);
        first=first->next;
    }
    printf("\n");
}



void push(Node** first, int key){
    if(*first==NULL){
        *first = create(key);
        return;
    }

    Node *newNode = create(key);
    newNode->next = *first;
    *first = newNode;
}

int pop(Node** first){
    if(*first==NULL)return -1;
    Node *p=*first;
    int a = (*first)->key;
    *first = (*first)->next;
    free(p);

    return a;
}




int main()
{
    Node* stack = NULL;
    printf("%d\n", pop(&stack));
    push(&stack, 2);
    push(&stack, 3);
    push(&stack, 4);
    push(&stack, 5);
    push(&stack, 6);
    afisare(stack);
    printf("%d\n", pop(&stack));
    afisare(stack);
    return 0;
}








//void push(Node** first, int key){
//    if(*first==NULL){
//        *first = create(key);
//        return;
//    }
//    Node * lastNode = (*first);
//    while(lastNode->next!=NULL){
//        lastNode=lastNode->next;
//    }
//    Node *newNode = create(key);
//    lastNode->next = newNode;
//}
//
//
//int pop(Node** first){
//    if(*first==NULL)return -1;
//    Node * secondLastNode = (*first);
//    while(secondLastNode->next->next!=NULL){
//        secondLastNode=secondLastNode->next;
//    }
//    Node * lastNode = secondLastNode->next;
//    secondLastNode->next = NULL;
//    int a = lastNode->key;
//    free(lastNode);
//
//    return a;
//}
