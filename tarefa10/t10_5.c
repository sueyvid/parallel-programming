// race_condition.c
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <omp.h>

#define N 1000000
#define THREADS 4

int main() {
    int total_count = 0;

    #pragma omp parallel
    {
        unsigned int seed = time(NULL) ^ omp_get_thread_num();
        
        #pragma omp for reduction(+:total_count)
        for (int i = 0; i < N; i++) {
            double x = rand_r(&seed) / (double)RAND_MAX;
            double y = rand_r(&seed) / (double)RAND_MAX;
            if (x * x + y * y <= 1) {
                total_count++;
            }
        }
    }

    double pi = 4.0 * total_count / N;
    printf("Pi = %f\n", pi);

    return 0;
}