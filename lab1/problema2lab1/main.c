#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int cap;
    int n;
    float *a;
} sir;

void init(sir *s)
{
    s->cap = 6;
    s->n=0;
    s->a=calloc(s->cap, sizeof(float));
}

void insert_first(sir *s, float x)
{
    if(s->n==s->cap)
    {
        s->cap*=2;
        s->a=realloc(s->a, s->cap * sizeof(float));
    }
    for(int i=s->n;i>0;i--){
        s->a[i]=s->a[i-1];
    }
    s->a[0]=x;
    ++(s->n);
}

void insert_last(sir *s, float x)
{
    if(s->n==s->cap)
    {
        s->cap*=2;
        s->a=realloc(s->a, s->cap * sizeof(float));
    }
    s->a[s->n]=x;
    ++(s->n);
}

void afisare(sir *s)
{
    for(int i=0; i<s->n; i++)
    {
        printf("%.2f ", s->a[i]);
    }
}

int main()
{
    sir s;
    init(&s);
    printf("Insert last:\n");
    for(int i=1; i<=5; ++i)
    {
        //insert_last(&s, i);
        insert_first(&s, i);
        afisare(&s);
        printf("\n");
    }

    free(s.a);

    return 0;
}
