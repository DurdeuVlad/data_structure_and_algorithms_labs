#include <stdio.h>
#include <malloc.h>
#include <minmax.h>

typedef struct node{
    int key;
    struct node*left;
    struct node*right;
}NodeT;

NodeT* create(int key){
    NodeT * q = malloc(sizeof(NodeT));
    q->key = key;
    q->left = q->right = NULL;
    return q;
}

NodeT * read(FILE *f){
    char s[100];
    fscanf(f, "%s", s);
    if(s[0]=='#')
        return NULL;
    int x = atoi(s);
    NodeT * q = create(x);
    q->left = read(f);
    q->right = read(f);
    return q;
}

void preorder(NodeT* first){
    if(first == NULL){
        printf("# ");
        return;
    }
    printf("%d ", first->key);
    preorder(first->left);
    preorder(first->right);
}

void inorder(NodeT* first){
    if(first == NULL){
        printf("# ");
        return;
    }
    inorder(first->left);
    printf("%d ", first->key);
    inorder(first->right);
}

void postorder(NodeT* first){
    if(first == NULL){
        printf("# ");
        return;
    }
    postorder(first->left);
    postorder(first->right);
    printf("%d ", first->key);
}

int leaf_node(NodeT *node){
    if (node == NULL) return 0;
    else if ((node->left == NULL) && (node->right == NULL)) return 1;
    return leaf_node(node->left)+leaf_node(node->right);
}

int internal_node(NodeT *node){
    if (node == NULL) return 0;
    else if ((node->left == NULL) && (node->right == NULL)) return 0;
    return internal_node(node->left)+internal_node(node->right)+1;
}

int inaltime(NodeT *node){
    if (node == NULL) return -1;
    return 1 + max(inaltime (node->left), inaltime (node->right));
}

NodeT * search(NodeT *first, int key){
    if(first == NULL){
        printf("# ");
        return NULL;
    }
    printf("%d ", first->key);
    if(first->key==key) return first;
    NodeT* cautare = search(first->left, key);
    if(cautare!=NULL)
        return cautare;
    return search(first->right, key);
}

int diametru_arbore(NodeT * first){
    if(first==NULL)return 0;
    return inaltime(first->right)+inaltime(first->left)+2;
}

int main() {
    FILE *in = fopen("arbore.txt", "r");
    NodeT *first = read(in);
    fclose(in);
    preorder(first);
    printf("\n");
    inorder(first);
    printf("\n");
    postorder(first);
    printf("\n leaf_node = %d", leaf_node(first));
    printf("\n internal_node = %d", internal_node(first));
    int search_for = 3;
    printf("\n inaltime = %d\nSearching for %d: ", inaltime(first), search_for);
    NodeT *toSearch = search(first, search_for);
    if (toSearch != NULL) {
        printf("\n search = %d\nCalculating height for %d: ", toSearch->key, search_for);
        printf("\n height = %d\n", inaltime(toSearch));
    }
    else {
        printf("Nu gaseste %d", search_for);
    }
    printf("\n diametru = %d\n", diametru_arbore(first));
    //1 2 # # 3 4 # 6 # # 7 # 8 # 9 # #

    return 0;
}
