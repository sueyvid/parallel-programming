// calculo_de_pi
#include <stdio.h>
#include <math.h>

#define LIMIT 200000

int is_prime(int n) {
    if (n < 2) return 0;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return 0;
    }
    return 1;
}

int main() {
    int count = 0;
    for (int rep = 0; rep < 500; rep++) {
        count = 0;
        #pragma omp parallel for
        for (int i = 2; i < LIMIT; i++) {
            if (is_prime(i)) {
                count++;
            }
        }
    }

    printf("Primos encontrados: %d\n", count);

    // compilar com: gcc -fopenmp t4_2.c -o t4_2

    // antes do for:
    // #pragma omp parallel for
    // for (...)

    // executar com: export OMP_NUM_THREADS=2; time ./t4_2

    return 0;
}
