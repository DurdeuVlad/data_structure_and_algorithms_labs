#include <stdio.h>
#include <malloc.h>

typedef struct node
{
    int key;
    struct node* left;
    struct node* right;
} NodeT;

NodeT* createNode(int key)
{
    NodeT* p = (NodeT*)malloc(sizeof(NodeT));
    p->key = key;
    p->left = NULL;
    p->right = NULL;
    return p;
}


NodeT* insert(NodeT** root, int key){
    if (*root == NULL)
    {
        *root = createNode(key);
    }
    else{
        NodeT * q = *root;
        while(q != NULL){
            if (key < q->key)
            {
                if(q->left == NULL)
                {
                    q->left = createNode(key);
                    break;
                }
                else
                    q = q->left;
            }
            else if (key > q->key)
            {
                if(q->right == NULL)
                {
                    q->right = createNode(key);
                    break;
                }
                else
                    q = q->right;
            }
            else
                break;
        }
    }
}


void inordine(NodeT* root)
{
    if (root == NULL) { return;}
    inordine(root->left);
    printf("%d, ", root->key);
    inordine(root->right);

}

void preOrder( NodeT *root){
    if (root == NULL) { printf("# "); return;}
    printf("%d ", root->key);
    preOrder(root->left);
    preOrder(root->right);

}

void postOrder( NodeT *root){
    if (root == NULL) { printf("# "); return;}
    postOrder(root->left);
    postOrder(root->right);
    printf("%d ", root->key);
}

NodeT *searchKey(NodeT* root, int key){
    if (root == NULL)
        return NULL;
    if (root->key == key)
        return root;
    if (key < root->key)
        return searchKey(root->left, key);
    else
        return searchKey(root->right, key);
}
NodeT *searchForParentOfKey(NodeT* root, int key){
    if (root == NULL || root->key == key)
        return NULL;
    if (root->left->key == key)
        return root->left;
    else if(root->right->key == key)
        return root->right;
    if (key < root->key)
        return searchKey(root->left, key);
    else
        return searchKey(root->right, key);

}

NodeT* findMin(NodeT* node){
    if (node == NULL)
        return NULL;
    if (node->left)
        return findMin(node->left);
    else
        return node;
}

NodeT* findMax(NodeT* node){
    if (node == NULL)
        return NULL;
    if (node->right)
        return findMax(node->right);
    else
        return node;
}


NodeT* succesor(NodeT*root, NodeT *node){
    if (node == NULL)
        return NULL;
    if (node->right)
        return findMin(node->right);
    NodeT* Succesor = NULL;
    while (root != NULL){
        if (node->key < root->key){
            Succesor = root;
            root = root->left;
        }
        else if (node->key > root->key)
            root = root->right;
        else
            break;
    }
    return Succesor;
}

NodeT* predecesor(NodeT*root, NodeT *node){
    if (node == NULL)
        return NULL;
    if (node->left)
        return findMax(node->left);
    NodeT* Predecessor = NULL;
    while (root != NULL){
        if (node->key > root->key){
            Predecessor = root;
            root = root->right;
        }
        else if (node->key < root->key)
            root = root->left;
        else
            break;
    }
    return Predecessor;
}

NodeT* deleteNode(NodeT* root, int key) {
    NodeT *p;
    if (root == NULL) return root;
    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else {
        if (root->left == NULL) {
            p = root->right;
            free(root);
            return p;
        }
        else if (root->right == NULL) {
            p = root->left;
            free(root);
            return p;
        }
        p = findMin(root->right);
        root->key = p->key;
        root->right = deleteNode(root->right, p->key);
    }
    return root;
}


int main() {
    NodeT* root = NULL;
    int intlist[]={100, 200, 150, 210, 155, 160, 157};
    for(int i=0;i<7;i++){
        insert(&root, intlist[i]);
    }

    //postOrder(root);
    //preOrder(root);
    inordine(root);
    printf("Max: %d ", findMax(root)->key);
    printf("Min: %d\n", findMin(root)->key);



    for(int i=1;i<7;i++){
    int x = intlist[i];

    NodeT * nodeT = searchKey(root, x);
    if(nodeT != NULL){
        printf("Max from %d: %d ", x, findMax(searchKey(root, x))->key);
        printf("Min from %d: %d\n", x, findMin(searchKey(root, x))->key);
    }
    else{
        printf("Nu exista nodul\n");
    }
    NodeT* node =  succesor(root, searchKey(root, x));
    if (node == NULL)
        printf("Nu exista succesor\n");
    else
        printf("Succesorul lui %d este %d\n", x,node->key);
    node =  predecesor(root, searchKey(root, x));
    if (node == NULL)
        printf("Nu exista predecesor\n");
    else
        printf("Predecessorul lui %d este %d\n", x,node->key);
    }

    for(int i=1;i<7;i++){
        printf("\n");
        inordine(deleteNode(root, intlist[i]));

    }
    return 0;
}
