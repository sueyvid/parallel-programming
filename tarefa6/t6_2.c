// race_condition.c
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <omp.h>

#define n 10000000

float gerar_numero() {
    // Gera um número pseudoaleatório
    float numero = ((float) rand() / RAND_MAX) * 2.0f;

    // printf("Número aleatório: %f\n", numero);

    return numero;
}

float distancia_entre(float x, float x_, float y, float y_) {
    // float x = 2; float y = 1;
    // int x_ = 1; int y_ = 1;

    double resultado;
    float x2; float y2;

    x2 = (x - x_) * (x - x_);
    y2 = (y - y_) * (y - y_);

    resultado = sqrt(x2 + y2);

    // printf("Resultado: %f\n", resultado);

    return resultado;
}

int main() {
    // Define a semente para srand() usando a hora atual do sistema
    srand(time(NULL));

    int count = 0; int total_count = 0;
    int r = 1;
    int x_ = 1; int y_ = 1;

    // printf("Threads max: %d", omp_get_max_threads());

    #pragma omp parallel firstprivate(count) shared(x_, y_, total_count)
    {
        // int count = 0;
        # pragma omp for
        for (int i = 0; i < n; i++){
            float x; float y;
            x = gerar_numero();
            y = gerar_numero();
            if (distancia_entre(x, x_, y, y_) <= 1) {// (x, y) dentro do círculo
                count++;
            }
        }
        # pragma omp critical
        total_count += count;
    }

    double pi = 4.0 * total_count / n;
    printf("Count: %d\n", total_count);
    printf("Pi: %f\n", pi);

    // compilar com: gcc -fopenmp t6_2.c -o t6_2 -lm

    // antes do for:
    // #pragma omp parallel for
    // for (...)

    // executar com: export OMP_NUM_THREADS=2; time ./t6_2

    return 0;
}
