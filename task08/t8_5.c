// race_condition.c
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <omp.h>

#define N 1000000
#define THREADS 4

typedef struct {
    int valor;
    char padding[64 - sizeof(int)];
} PaddedInt;

int main() {
    PaddedInt counts[THREADS];

    // inicializa counts
    for (int i = 0; i < THREADS; i++) {
        counts[i].valor = 0;
    }

    #pragma omp parallel num_threads(THREADS)
    {
        int tid = omp_get_thread_num();
        unsigned int seed = time(NULL) ^ (tid * 7919);

        #pragma omp for
        for (int i = 0; i < N; i++) {
            double x = rand_r(&seed) / (double)RAND_MAX;
            double y = rand_r(&seed) / (double)RAND_MAX;
            if (x * x + y * y <= 1) {
                counts[tid].valor++;
            }
        }
    }

    int total_count = 0;
    for (int t = 0; t < THREADS; t++) {
        total_count += counts[t].valor;
    }

    double pi = 4.0 * total_count / N;
    printf("Pi = %f\n", pi);

    return 0;
}