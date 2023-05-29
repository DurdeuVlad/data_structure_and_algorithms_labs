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


typedef struct{
    int varf, *v;
}Stiva;

int pop(Stiva* stiva){
    int key = stiva->v[stiva->varf];
    stiva->varf--;
    return key;
}

int push(Stiva* stiva, int key){
    stiva->varf++;
    stiva->v[stiva->varf] = key;
}

void DFS(Graf g, int start){
    Stiva stiva;
    stiva.v = calloc(g.n+1, sizeof(int));
    stiva.varf = 0;
    int* vizitat = calloc(g.n+1, sizeof(int));
    push(&stiva, start);
    while(stiva.varf!=0){
        int u = pop(&stiva);
        if(vizitat[u]==0){
            printf("%d ", u);
            vizitat[u]++;
            for(int i=0; i<g.n; i++){
                if(g.m[u][i]==1 && vizitat[i]==0){
                    push(&stiva, i);
                }
            }

        }
    }
}

void DFS_recursiv(Graf g, int start, int* vizitat){
    vizitat[start]++;
    printf("%d ", start);
    for(int i=0; i<g.n; i++){
        if(g.m[start][i]==1 && vizitat[i]==0){
            DFS_recursiv(g, i, vizitat);
        }
    }
}

void connect_neorientat(Graf *graf, int x, int y) {
    graf->m[x][y]=1;
    graf->m[y][x]=1;
}

void connect_orientat(Graf *graf, int x, int y) {
    graf->m[x][y]=1;
}

int DFS_Exista_Ciclu(Graf g, int start) {
    Stiva stiva;
    stiva.v = calloc(g.n + 1, sizeof(int));
    stiva.varf = 0;
    int *vizitat = calloc(g.n + 1, sizeof(int));
    push(&stiva, start);
    while (stiva.varf != 0) {
        int u = pop(&stiva);
        if (vizitat[u] == 0) {
            vizitat[u]++;
            for (int i = 0; i < g.n; i++) {
                if (g.m[u][i] == 1 && vizitat[i] == 0) {
                    push(&stiva, i);
                }
            }

        } else {
            return 1;
        }
    }
}



int return_road(Graf graf, int start, int y, Stiva *stiva) {
    stiva->v = calloc(graf.n + 1, sizeof(int));
    stiva->varf = 0;
    int *vizitat = calloc(graf.n + 1, sizeof(int));
    push(stiva, start);
    vizitat[start]++;
    while (stiva->varf != 0) {
        int u = pop(stiva);
        if (vizitat[u] == 0) {
            vizitat[u]++;
            for (int i = 0; i < graf.n; i++) {
                if (graf.m[u][i] == 1 && vizitat[i] == 0) {
                    push(stiva, i);
                }
            }

        } else {
            if (u == y) {
                return 1;
            }
        }
    }
    return 0;
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
    printf("\n");
    for(int i=0; i<graf.n; i++) {
        DFS_recursiv(graf, i, calloc(graf.n+1, sizeof(int)));
        printf("\n");
    }

    printf("\n");

    for(int i=0; i<graf.n; i++) {
        DFS(graf, i);
        printf("\n");
    }

    printf("\n");

    int x=0, y=1;
    Stiva stiva;
    int ok=return_road(graf, x++, y++, &stiva);
    printf("Este drum intre %d si %d? %d", x, y, ok);
    if(ok==1) {
        printf("\nDrumul este: ");
        for(int i=0; i<=stiva.varf; i++) {
            printf("%d ", stiva.v[i]);
        }
    }

    printf("\n");
    ok=0;
    for(int i=0; i<graf.n; i++) {
        ok = DFS_Exista_Ciclu(graf, i);

        if (ok == 1) {
            break;
        }
    }
    printf("Exista ciclu? %d", ok);


    return 0;
}
