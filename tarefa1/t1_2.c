// column_major.c
#include <stdio.h>
#include <stdlib.h>

void mul_matriz_vetor_coluna_externa(int **matriz, int *vetor, int *resultado, int linhas, int colunas) {
    // preencher vetor resultado
    for (int i = 0; i < linhas; i++) {
        resultado[i] = 0;
    }

    // multiplicar (varrendo colunas primeiro)
    for (int j = 0; j < colunas; j++) {
        for (int i = 0; i < linhas; i++) {
            resultado[i] += matriz[i][j] * vetor[j];
        }
    }
}

int main() {
    int n;
    printf("Digite o tamanho da matriz/vetor: ");
    scanf("%d", &n);

    // Alocar matriz n x n
    int **M = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        M[i] = (int *)malloc(n * sizeof(int));
    }

    // Preencher matriz
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            M[i][j] = i * n + j + 1;
        }
    }

    // Alocar vetor
    int *V = (int *)malloc(n * sizeof(int));

    // Preencher vetor
    for (int i = 0; i < n; i++) {
        V[i] = i + 1;
    }

    // Alocar resultado
    int *resultado = (int *)malloc(n * sizeof(int));

    // Multiplicação (MxV)
    mul_matriz_vetor_coluna_externa(M, V, resultado, n, n);

    // Liberar memória
    for (int i = 0; i < n; i++) {
        free(M[i]);
    }
    free(M);
    free(V);
    free(resultado);

    return 0;
}
