#include <stdio.h>
#include <stdlib.h>

typedef struct nod{
    int key;
    struct nod* next;
}NodeT;

//afisare
void afisare(NodeT* first){
    NodeT * p = first;
    while(p){
        printf("%d->", p->key);
        p = p->next;
    }
    printf("NULL\n");

}

NodeT* create(int givenkey){
    NodeT * node = malloc(sizeof(NodeT));
    node->key=givenkey;
    node->next=NULL;
    return node;
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


//cautare

NodeT* cautare(NodeT* first, int givenkey){
    NodeT * p = first;
    while(p && p->key!=givenkey){
        p = p->next;
    }
    return p;
}


//insert_after cu pointer
void insert_after(NodeT** first, NodeT** last, int searchkey, int givenkey){
    // cautam nodul pozitional
    NodeT * rezultat_cautare = cautare(&first, searchkey);
    if(rezultat_cautare==NULL) return;

        NodeT * p = create(givenkey);
        (*p).next = (*rezultat_cautare).next;
        (*rezultat_cautare).next = p;

        if(rezultat_cautare == *last){
            *last = p;
        }
}


void insert_last(NodeT** first, NodeT** last, int givenkey){
    // lista este goala
    if(*first == NULL){
        *first = *last = create(givenkey);
    }
    // lista contine un sigur element
    // lista este generala cel putin 2 elemente
    else {
        NodeT * p = create(givenkey);
        (*last)->next = p;
        *last = p;
    }

}

void delete_first(NodeT** first, NodeT** last){
    if(*first == NULL)return;
    NodeT *next = (*first)->next;
    free(*first);
    *first=next;
    if(next==NULL){
        last = NULL;
    }


}

void delete_last(NodeT** first, NodeT** last){
    if(*first == NULL)return;
    NodeT *next = *first;
    while(next != NULL && next->next != *last){
        next = next->next;
    }

    free(*last);
    *last=next;
    next->next=NULL;
    if(next==NULL){
        *last = NULL;
    }
}


void delete_key(NodeT** first, NodeT** last, int givenKey){
    if(*first == NULL)return;
    NodeT *before = *first;
    if(before->key !=givenKey){
        while(before != NULL && before->next->key != givenKey){
            before = before->next;
        }

        NodeT *next = before->next->next;
        free(before->next);
        before->next = next;
        if(next==NULL) *last=before;
    }
    else{
        NodeT *next = (*first)->next;
        free(*first);
        *first = next;
    }


}




int main()
{
    NodeT* first = NULL;
    NodeT* last = NULL;
    insert_last(&first, &last, 1);
    insert_first(&first, 2);
    insert_last(&first, &last, 3);
    insert_after(&first, &last, 3, 5);
    insert_after(&first, &last, 2, 5);
    insert_last(&first, &last, 6);
    afisare(first);
    delete_first(&first, &last);
    afisare(first);
    delete_last(&first, &last);
    afisare(first);
    delete_key(&first, &last, 5);
    afisare(first);
    return 0;
}
