#include <stdio.h>
#include <malloc.h>

int greedy_monede(int* bancnote, int length, int n){
    int x=0;
    for(int i=length-1;i>=0;i--){
        if(n-bancnote[i]>=0){
            int aux = n/bancnote[i];
            n = n-aux*bancnote[i];
            for(int j=0;j<aux;j++){
                printf("%d ", bancnote[i]);
            }
            x+=aux;
        }
    }
    if(n==0) return x;
    return -1;
}

typedef struct {
    int start, end;
    char* nume;
}Activitate;


int greedy_activitati(Activitate activitate[], int n){
int x=0;
    int last = 0;
    for(int i=0;i<n;i++){
        if(activitate[i].start>=last){
            printf("%s ", activitate[i].nume);
            last = activitate[i].end;
            x++;
        }
    }
    return x;

}

void sort_activitati(Activitate activitate[], int n){
    for(int i=0;i<n-1;i++){
        for(int j=i+1;j<n;j++){
            if(activitate[i].end>activitate[j].end){
                Activitate aux = activitate[i];
                activitate[i] = activitate[j];
                activitate[j] = aux;
            }
        }
    }

}

typedef struct {
    double greutate, valoare;
}Obiect;

int problema_rucsacului(Obiect obiecte[], int n, int G){
    int x=0;
    for(int i=0;i<n;i++){
        if(obiecte[i].greutate<=G){
            printf("%.2f ", obiecte[i].greutate);
            G-=obiecte[i].greutate;
            x+=obiecte[i].valoare;
        }
    }
    return x;

}

void sortare_iteme_dupa_greutate_per_pret(Obiect obiecte[], int n){
    for(int i=0;i<n-1;i++){
        for(int j=i+1;j<n;j++){
            if(obiecte[i].greutate/obiecte[i].valoare>obiecte[j].greutate/obiecte[j].valoare){
                Obiect aux = obiecte[i];
                obiecte[i] = obiecte[j];
                obiecte[j] = aux;
            }
        }
    }
}



int main() {
//    int bancnote[]= {1, 6, 10};
//    int n = 13;
//    int result = greedy_monede(bancnote, 3, n);
//    printf("Numarul de bancnote este: %d", result);
//    Activitate activitati[] = {{3, 6, "fac curatenie"},{7, 9, "cursuri de salsa"}, {10, 13, "biliard & bowling"},
//                               {4, 8, "picnic"},{9, 12, "foc de tabara"},
//                               {4, 6, "tenis"},{8, 10, "cina cu familia"},
//                               {6, 9, "invat la examen"},{10, 13, "concert de jazz"},
//                               {0, 6, "cu hamacul in parc"},{8, 11, "la film"},
//                               };
//
//    sort_activitati(activitati, 10);
//    int result = greedy_activitati(activitati, 10);
//    printf("Numarul de activitati este: %d", result);
    Obiect obiecte[] = {{1, 1}, {2, 6}, {5, 18}, {6, 22}, {7, 28}};
    sortare_iteme_dupa_greutate_per_pret(obiecte, 5);
    int result = problema_rucsacului(obiecte, 5, 11);
    printf("Valoarea maxima este: %d", result);
    return 0;
}
