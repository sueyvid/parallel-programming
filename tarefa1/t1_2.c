// column_major.c
#include <stdio.h>
#include <time.h>

const int m = 3;
const int n = 3;

void mul_matriz_vetor_linha_externa(int matriz[][3], int vetor[], int resultado[], int linhas, int colunas) {
    // preencher vetor resultado
    int i;
    for (i = 0; i < m; i++) {
        resultado[i] = 0;
    }

    // multiplicar
    for (int j = 0; j < colunas; j++) {
        for (int i = 0; i < linhas; i++) {
            resultado[i] += matriz[i][j] * vetor[j];
        }
    }
}

int main() {
    // Definição da matriz
    int M[m][n];
    int i, j;

    // preencher matriz
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            M[i][j] = i * m + j + 1;
        }
    }

    // imprimir matriz
    printf("Matriz:\n");
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            printf("%d ", M[i][j]);
        }
        printf("\n");
    }

    // Definição do vetor
    int V[m];

    // preencher vetor
    for (i = 0; i < m; i++) {
        V[i] = i + 1;
    }

    // imprimir vetor
    printf("Vetor:\n");
    for (int i = 0; i < 3; i++) {
        printf("%d ", V[i]);
    }
    printf("\n");

    // multiplicação (MxV)
    int resultado[m];

    mul_matriz_vetor_linha_externa(M, V, resultado, m, n);

    printf("Resultado da multiplicação:\n");
    for (int i = 0; i < m; i++) {
        printf("%d ", resultado[i]);
    }
    printf("\n");

    return 0;
}