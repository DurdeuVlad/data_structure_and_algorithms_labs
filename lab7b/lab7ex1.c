#include <stdio.h>
#include <malloc.h>

typedef struct {
    int n, **m;
} Graf;

typedef struct{
    int tail, head, *v, size;
}Coada;

enum {NEVISITAT, VISITAT};

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

void BFS(Graf *graf, int start) {
    if(start<0 || start>=graf->n) {
        printf("Nu e valid nodul de start!");
        return;
    }
    int *visited=(int*)calloc(sizeof(int)+1, graf->n);
    Coada queue;
    queue.v=(int*)malloc(graf->n * sizeof(int) + 1);
    queue.size=graf->n+1;
    queue.head=0, queue.tail=0;
    queue.v[queue.tail++]=start;
    visited[start]=VISITAT;
    while(queue.head!=queue.tail) {
        int y=dequeue(&queue);
        printf("%d ", y+1);
        for(int i=0; i<graf->n; i++) {
            if(graf->m[y][i]==1 && visited[i]==0) {
                enqueue(&queue, i);
                visited[i]=VISITAT;
            }
        }
    }
    printf("\n");
}

void connect_neorientat(Graf *graf, int x, int y) {
    graf->m[x][y]=1;
    graf->m[y][x]=1;
}

void connect_orientat(Graf *graf, int x, int y) {
    graf->m[x][y]=1;
}

int main() {
    Graf graf;
    FILE *in=fopen("input.txt", "r");
    fscanf(in, "%d", &graf.n);
    graf.m=(int**)malloc(graf.n*sizeof(int*));
    for(int i=0; i<graf.n; i++) {
        graf.m[i]=(int*)malloc(graf.n*sizeof(int));
        for(int j=0; j<graf.n; j++) {
            fscanf(in, "%d", &graf.m[i][j]);
        }
    }
    fclose(in);
    // print the matrix
    for(int i=0; i<graf.n; i++) {
        for(int j=0; j<graf.n; j++) {
            printf("%d ", graf.m[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    for(int i=0; i<graf.n; i++) {
        BFS(&graf, i);
    }

    return 0;
}
