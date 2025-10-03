// column_major.c
#include <stdio.h>
#include <stdlib.h>

void mul_matriz_vetor_coluna_externa(int **matriz, int *vetor, int *resultado, int linhas, int colunas) {
    for (int i = 0; i < linhas; i++) {
        resultado[i] = 0;
    }

    for (int j = 0; j < colunas; j++) {
        for (int i = 0; i < linhas; i++) {
            resultado[i] += matriz[i][j] * vetor[j];
        }
    }
}

int main() {
    int n = 4096;

    int **M = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        M[i] = (int *)malloc(n * sizeof(int));
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            M[i][j] = 1;
        }
    }

    int *V = (int *)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        V[i] = 1;
    }

    int *resultado = (int *)malloc(n * sizeof(int));

    mul_matriz_vetor_coluna_externa(M, V, resultado, n, n);

    for (int i = 0; i < n; i++) {
        free(M[i]);
    }
    free(M);
    free(V);
    free(resultado);

    return 0;
}
