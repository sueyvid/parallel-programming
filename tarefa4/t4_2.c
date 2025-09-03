// cpu_bound
#include <stdio.h>
#include <math.h>

#define N 8192

int main() {
    static int matrix[N][N];
    double result = 0.0;

    #pragma omp parallel for
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            double x = i * 0.000001;
            double val = sin(x) * cos(x) 
                    + log(x + 1.0) * exp(-x) 
                    + sqrt(x) * tanh(x);
            result += val;
        }
    }

    printf("Soma = %f\n", result);

    // compilar com: gcc -fopenmp t4_1.c -o t4_1

    // antes do for:
    // #pragma omp parallel for
    // for (...)

    // executar com: export OMP_NUM_THREADS=2; time ./t4_1

    return 0;
}