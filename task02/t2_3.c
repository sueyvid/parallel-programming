// soma_paralela_2.c
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
    int sum1 = 0; int sum2 = 0;
    int sum3 = 0; int sum4 = 0; int total = 0;
    for (int j = 0; j < reps; j++){
        total = 0;
        for (int i = 0; i < n; i+=4){
            sum1 += A[i];
            sum2 += A[i+1];
            sum3 += A[i+2];
            sum4 += A[i+3];
        }
        total = sum1 + sum2 + sum3 + sum4;
    }

    printf("Soma não-acumulativa: %d\n", total);
}