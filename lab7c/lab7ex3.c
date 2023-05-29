#include <stdio.h>
#include <malloc.h>

#define MAX 100

typedef struct {
    int head, tail, size;
    int* v;
}Coada;



typedef struct {
    int n, m;
    int liste[MAX][MAX]; //liste[u] = lista care stocheaza vecinii lui u
}Graf;


void insert_last(int liste[MAX][MAX], int v){
    printf("\ninsert_last(%d) ", v);
    for(int i=0; i<MAX; i++){
        if(liste[0][i]==-1){
            liste[0][i] = v;
            return;
        }
    }
}

void afiseaza(Graf graf){
    for(int i=1; i<=graf.n; i++){
        printf("Lista %d: ", i);
        int j=0;
        while(graf.liste[i][j]!=-1){
            printf("%d ", graf.liste[i][j]);
            j++;
        }
        printf("\n");
    }
}

void enqueue(Coada* coada, int key){
    coada->v[coada->tail] = key;
    coada->tail++;
    if(coada->tail >= coada->size){
        coada->tail = 0;
    }
}

int dequeue(Coada* coada){
    int key = coada->v[coada->head];
    coada->head++;
    if(coada->head >= coada->size){
        coada->head = 0;
    }
    return key;
}
enum {NEVISITAT, VISITAT};

void BFS(Graf *graf, int start){
    if(start<0 || start>=graf->n) {
        printf("Nu e valid nodul de start!");
        return;
    }
    int *visited=(int*)calloc(sizeof(int)+1, graf->n);
    Coada queue;
    queue.v=(int*)malloc(graf->n * sizeof(int) + 1);
    queue.size=graf->n+1;
    queue.head=0, queue.tail=0;
    enqueue(&queue, start);
    visited[start]=VISITAT;
    while(queue.head!=queue.tail) {
        int y=dequeue(&queue);
        printf("%d ", y+1);
        for(int i=0; i<graf->n; i++) {
            if(graf->liste[y][i]!=-1 && visited[graf->liste[y][i]]==NEVISITAT) {
                enqueue(&queue, graf->liste[y][i]);
                visited[graf->liste[y][i]]=VISITAT;
            }
        }
    }
    printf("\n");
}

int main() {
    Graf graf;
    for(int i=0; i<MAX; i++){
        for(int j=0; j<MAX; j++){
            graf.liste[i][j] = -1;
        }
    }
    FILE * in = fopen("input.txt", "r");
    if(in==NULL){
        printf("Could not open the file!");
        return 1;
    }
    fscanf(in, "%d", &graf.n);
    graf.m = 0;
    int u=0, v=0;
    while(fscanf(in, "%d %d", &u, &v)==2){
        //printf("u=%d, v=%d ", u, v);
        graf.m++;
        insert_last(&graf.liste[u], v);
    }
    printf("\n");
    afiseaza(graf);
    printf("\n");
    for(int i=1; i<graf.n; i++){
        BFS(&graf, i);
    }

    fclose(in);
    return 0;
}
