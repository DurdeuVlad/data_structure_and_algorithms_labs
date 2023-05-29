#include <stdio.h>
#include <stdlib.h>

#define MAX 100000

int bin_search(int v[], int x, int st, int dr){
    printf("dr = %d and st = %d ", dr, st);
    if(st>=dr){
        if(v[st]==x) return 1;
        return -1;
    }
    else
    {
        int m = (st+dr)/2;
        if(v[m]==x) return 1;
        else if(v[m]<x) return bin_search(v, x, m+1, dr);
        else if(v[m]>x) return bin_search(v, x, st, m);
    }

}


void mergesort(int v[], int n){
    if(n==2){
        if(v[0]>v[1]){
            int aux = v[0];
            v[0] = v[1];
            v[1] = aux;
        }
        return;
    }
    if(n<=1) return;
    int i = 0, j = n/2;
    mergesort(v, j);
    mergesort(v+j, n-j);
    int counter=-1;
    int aux[n];
    while(counter<n){
        counter++;
        if(i>=n/2){
            aux[counter]=v[j];
            j++;
        }
        else if(j>=n){
            aux[counter]=v[i];
            i++;
        }
        else if(v[i]<v[j]){
            aux[counter]=v[i];
            i++;
        }
        else{
            aux[counter]=v[j];
            j++;
        }
    }
    for(i=0;i<n;i++){
        v[i]=aux[i];
    }
}

void bubblesort(int v[], int n){
    int i, j;
    for(i=0;i<n;i++){
        for(j=0;j<n-i-1;j++){
            if(v[j]>v[j+1]){
                int aux = v[j];
                v[j] = v[j+1];
                v[j+1] = aux;
            }
        }
    }
}

void quicksort(int v[], int n){
    if(n<=1) return;
    int i=0, j=n-1;
    int pivot = v[n/2];
    while(i<=j){
        while(v[i]<pivot) i++;
        while(v[j]>pivot) j--;
        if(i<=j){
            int aux = v[i];
            v[i] = v[j];
            v[j] = aux;
            i++;
            j--;
        }
    }
    quicksort(v, j+1);
    quicksort(v+i, n-i);
}

int main() {


////   int v[]={10, 5, 4, 6};
////
////   int n=4;
//    printf("GENERATING VECTOR\n");
    int v[MAX];
    for(int i=0;i<MAX;i++) {
        v[i]= rand()%MAX;
        //printf("%d ", v[i]);
    }
    printf("MERGESORT VECTOR START\n");
    mergesort(v, MAX);
//    for(int i=0;i<MAX;i++){
//        printf("%d ", v[i]);
//    }
    printf("MERGESORT VECTOR END\n");

    printf("REGENERATING VECTOR\n");
    for(int i=0;i<MAX;i++) {
        v[i]= rand()%MAX;
        //printf("%d ", v[i]);
    }
    printf("BUBBLESORT VECTOR START\n");
    bubblesort(v, MAX);
//    for(int i=0;i<MAX;i++){
//        printf("%d ", v[i]);
//    }
    printf("BUBBLESORT VECTOR END\n");

    printf("QUICKSORT VECTOR START\n");
    quicksort(v, MAX);
//    for(int i=0;i<MAX;i++){
//        printf("%d ", v[i]);
//    }
    printf("QUICKSORT VECTOR END\n");

    for(int i=-5;i<=10;i++){
     printf("este %d? %d\n", i, bin_search(v,i,0,MAX-1));
    }
    return 0;
}
