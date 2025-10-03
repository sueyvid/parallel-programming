// diffusion.c
// gcc -O3 -fopenmp diffusion.c -o diffusion
// ./diffusion

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

#define IDX(i,j,Nx) ((j)*(Nx) + (i))

int main() {
    // Valores padrão
    int Nx = 200;      // número de pontos no eixo x
    int Ny = 200;      // número de pontos no eixo y
    int steps = 500;   // número de passos de tempo
    double nu = 0.01;  // viscosidade
    double dt = 0.0001; // passo de tempo

    double h = 1.0 / Nx;
    int N = Nx * Ny;

    double *w = calloc(N, sizeof(double));
    double *w_new = calloc(N, sizeof(double));

    // Perturbação inicial no centro
    int ic = Nx/2, jc = Ny/2;
    w[IDX(ic,jc,Nx)] = 1.0;

    double start = omp_get_wtime();

    for (int n = 0; n < steps; n++) {
        // 👉 Altere manualmente esta linha para testar:
        // #pragma omp parallel for
        // #pragma omp parallel for schedule(static)
        // #pragma omp parallel for schedule(dynamic,4)
        // #pragma omp parallel for collapse(2) schedule(static)
#pragma omp parallel for collapse(2) schedule(static)
        for (int j = 0; j < Ny; j++) {
            for (int i = 0; i < Nx; i++) {
                int ip = (i+1) % Nx;
                int im = (i-1+Nx) % Nx;
                int jp = (j+1) % Ny;
                int jm = (j-1+Ny) % Ny;

                double lap = ( w[IDX(ip,j,Nx)] + w[IDX(im,j,Nx)] +
                               w[IDX(i,jp,Nx)] + w[IDX(i,jm,Nx)] -
                               4.0 * w[IDX(i,j,Nx)] ) / (h*h);

                w_new[IDX(i,j,Nx)] = w[IDX(i,j,Nx)] + dt * nu * lap;
            }
        }
        // swap
        double *tmp = w; w = w_new; w_new = tmp;
    }

    double end = omp_get_wtime();
    printf("Simulation finished in %f seconds\n", end - start);
    printf("Center value = %f\n", w[IDX(Nx/2,Ny/2,Nx)]);

    free(w); free(w_new);
    return 0;
}
