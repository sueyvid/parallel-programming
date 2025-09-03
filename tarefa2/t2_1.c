// soma_sequencial.c
#include <stdio.h>

#define n 1000000
#define reps 1000

int main(){
    int A[n];

    // Inicializa o vetor A
    for (int i = 0; i < n; i++){
        A[i] = i;
    }

    // Soma sequencial
    int sum = 0;
    for (int j = 0; j < reps; j++){
        for (int i = 0; i < n; i++){
            sum += A[i];
        }
    }
    
    printf("Soma acumulativa: %d\n", sum);
}