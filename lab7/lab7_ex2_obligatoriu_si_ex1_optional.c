#include <stdio.h>
#include <malloc.h>

typedef struct {
    int head, tail, size;
    int* v;
}Coada;

typedef struct node{
    int x;
    struct node* next;
}NodeT;

typedef struct {
    int n, m;
    NodeT** liste; //liste[u] = lista care stocheaza vecinii lui u
}Graf;

NodeT* create(int key){
    NodeT* f = malloc(sizeof(NodeT));
    f->next = NULL;
    f->x = key;
    return f;
}

void insert_first(NodeT** liste, int v){
    //printf("insert_first(%d) ", v);
    if(*liste==NULL){
        *liste = create(v);
        return;
    }
    NodeT* f = liste[0];
    liste[0] = create(v);
    liste[0]->next = f;
}

void afiseaza(Graf graf){
    for(int i=1; i<=graf.n; i++){
        printf("Lista %d: ", i);
        NodeT* f = graf.liste[i];
        while(f!=NULL){
            printf("%d ", f->x);
            f = f->next;
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

int* BFS(Graf g, int start){
    Coada coada;
    coada.v=calloc(g.n+1, sizeof(int));
    coada.head = 0;
    coada.tail=0;
    int* vizitat=calloc(g.n+1, sizeof(int));
    int* level=calloc(g.n+1, sizeof(int));
    coada.size = g.n+1;
    // o sa bagam in coada pozitia de start
    enqueue(&coada, start);
    // THIS WHILE SHOULD ALSO KEEP TRACK OF THE LEVEL OF EACH NODE
    while(coada.tail != coada.head){
        //printf("BFS: coada->head=%d, coada->tail=%d", coada.head, coada.tail);
        int u = dequeue(&coada);
        if(vizitat[u]==0){
            printf("%d ", u);
            vizitat[u]++;
            NodeT* f = g.liste[u];
            while(f!=NULL){
                if(vizitat[f->x]==0){
                    coada.v[coada.tail]=f->x;
                    coada.tail++;
                    level[f->x]=level[u]+1;
                }
                f = f->next;
            }
        }
    }
    printf("\n");
    // returnam vectorul de vizitati prelucrat ca sa fie doar numerele vizitate in ordinea in care au fost vizitate
    return level;
}

int is_connected(Graf graf, int x, int y){
    NodeT*p = graf.liste[x];
    while(p!=NULL){
        if(p->x==y) return 1;
        p=p->next;
    }
    return 0;
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
            NodeT* f = g.liste[u];
            while(f!=NULL){
                if(vizitat[f->x]==0){
                    push(&stiva, f->x);
                }
                f = f->next;
            }
        }
    }
}

int DFS_returns_odd_cycle(Graf g, int start){
    Stiva stiva;
    stiva.v = calloc(g.n+1, sizeof(int));
    stiva.varf = 0;
    int* vizitat = calloc(g.n+1, sizeof(int));
    push(&stiva, start);
    // This while will keep track of the level of each node
    // if a node that was already visited is reached, that means we have a cycle
    // calculated the length of the cycle and return 1 if it is odd
    while(stiva.varf!=0){
        int u = pop(&stiva);
        if(vizitat[u]==0){
            vizitat[u]++;
            NodeT* f = g.liste[u];
            while(f!=NULL){
                if(vizitat[f->x]==0){
                    push(&stiva, f->x);
                }
                else{
                    // calculate the length of the cycle
                    int length = 0;
                    int i = stiva.varf;
                    while(stiva.v[i]!=f->x){
                        length++;
                        i--;
                    }
                    length++;
                    return length;

                }
                f = f->next;
            }
        }
    }
}

void is_graf_bipartit(Graf g){
    // this function will check all the conex elements of the graph and will check if they are bipartit
    // if they are not, it will print the length of the odd cycle
    int* vizitat = calloc(g.n+1, sizeof(int));
    for(int i=1; i<=g.n; i++){
        if(vizitat[i]!=0) continue;
        vizitat = BFS(g, i);
        int length = DFS_returns_odd_cycle(g, i);
        if(length%2==1 && length>1){
            printf("\nThe graph is not bipartit because it has an odd cycle of length %d", length);
            return;
        }

    }
    printf("\nThe graph is bipartit!");
}

int main() {
    Graf g;
    FILE * f = fopen("input.in", "r");
    if(f==NULL){
        printf("Could not open the file!");
        return 1;
    }
    fscanf(f, "%d", &g.n);
    g.liste = calloc(g.n+1, sizeof(NodeT*));
    g.m=0;
    int u=0, v=0;
    while(fscanf(f, "%d %d", &u, &v)==2){
        //printf("u=%d, v=%d ", u, v);
        g.m++;
        insert_first(&g.liste[u], v);
    }
    fclose(f);

    afiseaza(g);
    int startnode = 1;
    int* vizitati = BFS(g, startnode);
    DFS(g, startnode);
    printf("\n");
    for(int i=1; i<=g.n; i++){
        printf("%d ", vizitati[i]);
    }

    //printf("Are there any odd cycles starting from %d? %d\n", startnode,DFS_returns_odd_cycle(g, startnode));
    is_graf_bipartit(g);
    printf("\n");
    return 0;
}
