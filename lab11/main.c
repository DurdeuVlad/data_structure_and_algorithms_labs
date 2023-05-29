#include <stdio.h>


int min(int a, int b) {
    return a<b?a:b;
}

//    For i = 1 la S
//    For j = 0 la N -1
//    Daca (Vj <= i AND Min[i-Vj] + 1 < Min[i]) Atunci
//            Min[i] = Min[i - Vj] + 1
//    Output Min[S]
int desc_min(int a[], int s) {
    int dp[s+1];
    for(int i=0; i<=s; i++) {
        dp[i] = 1e9;
    }
    dp[0] = 0;

    for(int i=0;i<=s;i++){
        for(int j=0;j<=2;j++)
            if(a[j]<=i && dp[i-a[j]] + 1 < dp[i])
                dp[i] = dp[i-a[j]] + 1;
    }
    for(int i=0; i<=s; i++) {
        printf("%d ", dp[i]);
    }
    return dp[s];
}

//Ex. 1 — Plata unei sume S cu monede - varianta 1: Scrieti o functie care determina numarul maxim de combinatii
//în care poate fi platita o suma S, folosind monedele date.
int numarul_min(int a[], int s) {
    int dp[s+1];
    for(int i=0; i<=s; i++) {
        dp[i] = 0;
    }
    dp[0] = 1;
    for(int j=0;j<=2;j++)
        for(int i=0;i<=s;i++){
//            if cantitate >= val_monedei
//             combinatii[cantitate] += combinatii[cantitate - val_monedei]
            if(i>=a[j])
            {
                dp[i] += dp[i-a[j]];
            }
    }
    for(int i=0; i<=s; i++) {
        printf("%d ", dp[i]);
    }
    return dp[s];
}

int max(int a, int b) {
    return a>b?a:b;
}

int prob_rucsacului(int g[], int v[], int G, int n) {
    int dp[G+1];
    for(int i=0; i<=G; i++) {
        dp[i] = 0;
    }

    for (int j = 1; j <= n; j++)
        for (int i = G; i >= 0; i--)
            if (i >= g[j-1])
                dp[i] = max(dp[i], dp[i - g[j-1]] + v[j-1]);


    for(int i=0; i<=G; i++) {
        printf("%d ", dp[i]);
    }
    return dp[G];
}

int main() {
    int g[] = {2, 4, 8, 7};
    int v[] = {5, 6, 13, 5};
    int n=4;
    printf("Result: %d\n", prob_rucsacului(g, v, 9, n));
    return 0;
}
