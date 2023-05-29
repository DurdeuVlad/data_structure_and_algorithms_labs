#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char nume[20], prenume[20];
    int varsta, note[3];
    double medie;
}STUDENT;

int main()
{
    int student_nr = 0;
    FILE*in = fopen("intrare.txt", "r");
    fscanf(in, "%d", &student_nr);
    //alocare dinamica lista studenti
    STUDENT *student_lista = malloc(sizeof(STUDENT)*student_nr);
    printf("CITIRE.\n");
    for(int i=0;i<student_nr;i++){
        fscanf(in, "%s %s %d %d %d %d",
               student_lista[i].nume, student_lista[i].prenume,
               &student_lista[i].varsta, &student_lista[i].note[0],
               &student_lista[i].note[1], &student_lista[i].note[2]);


    }
    fclose(in);
    printf("AFISARE:\n");
    for(int i=0;i<student_nr;i++){
        student_lista[i].medie = 0;
        for(int j=0;j<3;j++){
            student_lista[i].medie += student_lista[i].note[j];
        }
        student_lista[i].medie /= 3;
        printf("%d. %s %s %d %d %d %d\n", i,
               student_lista[i].nume, student_lista[i].prenume,
               student_lista[i].varsta, student_lista[i].note[0],
               student_lista[i].note[1], student_lista[i].note[2]);
    }
    printf("MEDIE:\n");
    for(int i=0;i<student_nr;i++){
        printf("%d. %s %s Medie: %.2f\n", i,
               student_lista[i].nume, student_lista[i].prenume,
                student_lista[i].medie);
    }
    printf("INCREMENTARE:\n");
    for(int i=0;i<student_nr;i++){
        printf("%d. %s %s %d %d %d\n", i,
               student_lista[i].nume, student_lista[i].prenume,
               ++student_lista[i].note[0],
               ++student_lista[i].note[1], ++student_lista[i].note[2]);
    }
    return 0;
}
