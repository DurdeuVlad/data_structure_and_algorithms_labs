#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
// 1. generati permutarile multimii 1, 2, ..., n
void bt(int k, int n, int* X){
    // am terminat de construit solutia
    if(k==n){
        for(int i=0;i<n;i++){
            printf("%d ",X[i]);
        }
        printf("\n");
        return;
    }

    // incercam fiecare element posibil pe pozitia k
    for(int x=1;x<=n;x++){
        X[k]=x;

        // verificarea solutiei partiale
        int ok=1;
        for(int i=0;i<k;i++){
            if(X[i]==X[k]){
                ok=0;
                break;
            }
        }
        if(ok)
            bt(k+1,n,X);
    }

}


// generati/afisati/numarati solutiile
// 2. toate permutarile multimii a, a+1, ..., b
// ( b-a+1 )!

void generare_permutari(int k, int a, int b, int* X, int* count){
    // am terminat de construit solutia
    int n=b-a+1;
    if(k==n){
        for(int i=0;i<n;i++){
            printf("%d ",X[i]);
        }
        (*count)++;
        printf("\n");
        return;
    }

    // incercam fiecare element posibil pe pozitia k
    for(int x=a;x<=b;x++){
        X[k]=x;

        // verificarea solutiei partiale
        int ok=1;
        for(int i=0;i<k;i++){
            if(X[i]==X[k]){
                ok=0;
                break;
            }
        }
        if(ok){
            generare_permutari(k+1,a,b,X, count);
        }
    }

}


// 3. toate sirurile strict descrescatoare de lungime n cu elemente intre [1,m]
// ( n )
// ( m )
void generare_siruri_strict_descrescatoare(int k, int n, int m, int* X, int *count){
    // am terminat de construit solutia
    if(k==n){
        for(int i=0;i<n;i++){
            printf("%d ",X[i]);
        }
        (*count)++;
        printf("\n");
        return;
    }

    // incercam fiecare element posibil pe pozitia k
    for(int x=1;x<=m;x++){
        X[k]=x;

        // verificarea solutiei partiale
        int ok=1;
        if(k>=1){
            if(X[k-1]<=X[k]){
                ok=0;
                break;
            }
        }
//        for(int i=0;i<k;i++){
//            if(X[i]<=X[k]){
//                ok=0;
//                break;
//            }
//        }
        if(ok)
            generare_siruri_strict_descrescatoare(k+1,n, m, X, count);
    }

}

// 4. toate stringurile care alterneaza consoanele si vocalele
//
void stringuri_alterneaza_consoane_vocale(int k, int n, int *X, int *count){
    // am terminat de construit solutia
    if(k==n){
        for(int i=0;i<n;i++){
            printf("%c ",X[i]);
        }
        (*count)++;
        printf("\n");
        return;
    }

    // incercam fiecare element posibil pe pozitia k
    for(int x='a';x<='z';x++){
        //if(x<'a' && x>'Z')
        //    continue;

        X[k]=x;
        // verificarea solutiei partiale
        int ok=1;

        if(k>=1){
            int vocala_anterior=strchr("aeiou", X[k-1])!=NULL;
            int vocala_current=strchr("aeiou", X[k])!=NULL;
            if(vocala_anterior==vocala_current){
                ok=0;
            }
        }
        if(ok)
            stringuri_alterneaza_consoane_vocale(k+1,n, X, count);
    }
}

// 5. problema damelor, doar ca daca va avea o functie custom de atac
typedef struct{
    int x, y;
}Point;

void problema_damelor(int k, int n, Point* X, int *count, int attack_function(Point, Point)){
    // am terminat de construit solutia
    if(k==n){
        for(int i=0;i<n;i++){
            printf("(%d,%d) ",X[i].x, X[i].y);
        }
        (*count)++;
        printf("\n");
        return;
    }

    // incercam fiecare element posibil pe pozitia k
    int xmin=0;
    if(k>0){
        xmin=X[k-1].x;
    }
    for(int x=xmin;x<n;x++){
        for(int y=0;y<n;y++){
            if(k>0)
                if(x==xmin && y<=X[k-1].y)
                    continue;
            X[k].x=x;
            X[k].y=y;
            // verificarea solutiei partiale
            int ok=1;
            for(int i=0;i<k;i++){
                if(attack_function(X[i], X[k])){
                    ok=0;
                    break;
                }
            }
            if(ok){
                problema_damelor(k+1, n, X, count, attack_function);
            }
        }
    }


}

int attack_tura_rege(Point a, Point b){
    if(a.x==b.x || a.y==b.y)
        return 1;
    // check if it attacks like a king
    if(abs(a.x-b.x)+abs(a.y-b.y)==2)
        return 1;
    return 0;
}

int main() {
    int n=5, m=10, count=0;
    int X[10];
    Point pointX[100];
    //generare_permutari(0, n, m,X, &count);
    //generare_siruri_strict_descrescatoare(0, n, m, X, &count);
    //stringuri_alterneaza_consoane_vocale(0, n, X, &count);
    problema_damelor(0, n, pointX, &count, attack_tura_rege);
    printf("%d", count);
    return 0;
}
