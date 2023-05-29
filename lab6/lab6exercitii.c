#include <stdio.h>
#include <malloc.h>

#define size 7

typedef struct node {
    int key;
    struct node* next;
} NodeT;

void insertElement(NodeT* hTable[size], int key, int function(int))
{
    int hash = function(key);
    NodeT* p = (NodeT*)malloc(sizeof(NodeT));
    p->key = key;
    p->next = hTable[hash];
    hTable[hash] = p;
}

int insertElementLinear(NodeT* hTable[size], int key, int function(int), int verification(int, int))
{
    int hash = function(key);
    NodeT* p = (NodeT*)malloc(sizeof(NodeT));
    p->key = key;
    p->next = NULL;
    for(int i=0;i<=size;i++){
        int new_hash = function(verification(hash, i));
        if(hTable[new_hash]==NULL){
            hTable[new_hash] = p;
            return 0;
        }
    }
    return 1;

}
NodeT* findElement(NodeT* hTable[size], int key, int function(int)) {
    int hash = function(key);
    for(int i=0;i<=size;i++){
        int new_hash = function(hash+i);
        if(hTable[new_hash]==key){
            return hTable[new_hash];
        }
    }
}

NodeT* findElementLinear(NodeT* hTable[size], int key, int hashcalculator(int), int verification(int, int))
{
    int hash = hashcalculator(key);
    for(int i=0;i<=size;i++){
        if(hTable[hash+i]==NULL){
            continue;
        }
        int new_hash = hashcalculator(verification(hash, i));
        if(hTable[new_hash]->key==key){
            return hTable[new_hash];
        }
    }
    return NULL;
}

//void deleteElementLinear(NodeT* hTable[size], int key, int function(int), int verificare(int, int)){
//    NodeT *p = findElementLinear(hTable, key, function, verificare);
//    if(p==NULL){
//        return;
//    }
//    for(int i=0;i<=size;i++){
//        int new_hash = function(key+i);
//        if(hTable[new_hash]==p){
//            hTable[new_hash] = NULL;
//        }
//    }
//    free(p);
//}

void deleteElement(NodeT* hTable[size], int key, int function(int))
{
    int hash = function(key);
    NodeT* p = hTable[hash];
    NodeT* q = NULL;
    while (p != NULL)
    {
        if (p->key == key)
        {
            if (q == NULL)
                hTable[hash] = p->next;
            else
                q->next = p->next;
            free(p);
            return;
        }
        q = p;
        p = p->next;
    }
}

int h1(int key){
    key = key % size;
    if(key<0){
        key = key+ size;
    }
    return key;
}


int verficare_polinomiala(int key, int i){
    return h1(key)+i+i*i;
}

int verificare_simpla(int key, int i){
    return h1(key)+i;
}

//h(k, i) = (h1(k) + i × h2(k)) mod m
// 5 − (k mod 5)
int h2(int key){
    return (5 - (key % 5));
}

int verificare_dubla(int key, int i){
    return (h1(key)+i*h2(key))%size;
}




void showHash(NodeT* hTable[size])
{
    for (int i = 0; i < size; i++)
    {
        NodeT* p = hTable[i];
        printf("%d: ", i);
        if(p == NULL){
            printf("NULL\n");
            continue;
        }
        while (p != NULL)
        {
            printf("%d ", p->key);
            p = p->next;
        }
        printf("\n");
    }
}

int main() {
    NodeT* hTable[size];
    for (int i = 0; i < size; i++)
        hTable[i] = NULL;

    // TEST PRIMUL EXERCITIU
    //int keys[] = {  36, 14, 26, 21, 5, 19,4 };
//    for (int i = 0; i < 6; i++)
//        insertElement(hTable, keys[i], h1);
//    showHash(hTable);
//    int searchKey = 5;
//    NodeT* nodeT = findElement(hTable, searchKey, h1);
//    if(nodeT != NULL){
//        printf("%d\n", nodeT->key);
//        deleteElement(hTable, searchKey, h1);
//        printf("Stergem nodul %d: \n", searchKey);
//        showHash(hTable);
//    }
//    else {
//        printf("Nu exista nodul cautat.\n");
//    }

//    // TEST AL DOILEA EXERCITIU
//    int keys[] = {  19, 36, 5, 21, 4, 26, 14 };
//    for (int i = 0; i < 7; i++)
//        insertElementLinear(hTable, keys[i], h1, verificare_simpla);
//    showHash(hTable);


//    // TEST AL TREILEA EXERCITIU
//    int keys[] = {  19, 36, 5, 21, 4, 26, 14 };
//    for (int i = 0; i < 7; i++)
//        insertElementLinear(hTable, keys[i], h1, verficare_polinomiala);
//    showHash(hTable);

    // TEST AL PATRULEA EXERCITIU
    int keys[] = {  19, 36, 5, 21, 4, 26, 14 };
    for (int i = 0; i < 7; i++)
        insertElementLinear(hTable, keys[i], h1, verificare_dubla);
    showHash(hTable);





    return 0;
}
