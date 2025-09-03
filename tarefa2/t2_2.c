// soma_paralela.c
#include <stdio.h>

#define n 1000000
#define reps 1000

int main(){
    int A[n];

    // Inicializa o vetor A
    for (int i = 0; i < n; i++){
        A[i] = i;
    }

    // Soma paralela
    int sum1 = 0; int sum2 = 0; int total = 0;
    for (int j = 0; j < reps; j++){
        total = 0;
        for (int i = 0; i < n; i+=2){
            sum1 += A[i];
            sum2 += A[i+1];
        }
        total = sum1 + sum2;
    }

    printf("Soma não-acumulativa: %d\n", total);
}