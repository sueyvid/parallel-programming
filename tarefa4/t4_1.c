// memory_bound
#include <stdio.h>

#define N 8192

int main() {
    static int matrix[N][N];
    long long sum = 0;

    // Preenche a matriz com alguns valores
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            matrix[i][j] = 1;
        }
    }

    // Acesso column-major
    #pragma omp parallel for
    for (int j = 0; j < N; j++) {
        for (int i = 0; i < N; i++) {
            sum += matrix[i][j];
        }
    }

    printf("Soma = %lld\n", sum);

    // compilar com: gcc -fopenmp t4_1.c -o t4_1

    // antes do for:
    // #pragma omp parallel for
    // for (...)

    // executar com: export OMP_NUM_THREADS=2; time ./t4_1

    return 0;
}