#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define IDX(i,j,k,Nx,Ny) (((k)*(Ny)*(Nx)) + ((j)*(Nx)) + (i))

int main(int argc, char *argv[]) {
    // Parâmetros padrão
    int Nx = 100, Ny = 100, Nz = 100; // grade 3D
    int steps = 100;                // número de passos no tempo
    double nu = 0.01;              // viscosidade
    double dt = 0.0005;            // passo no tempo
    double h = 1.0 / Nx;

    steps = atoi(argv[1]);

    int N = Nx * Ny * Nz;

    double *w = calloc(N, sizeof(double));
    double *w_new = calloc(N, sizeof(double));

    // Perturbação inicial no centro
    int ic = Nx/2, jc = Ny/2, kc = Nz/2;
    w[IDX(ic,jc,kc,Nx,Ny)] = 1.0;

    for (int n = 0; n < steps; n++) {
#pragma omp parallel for collapse(3) schedule(guided)
        for (int k = 0; k < Nz; k++) {
            for (int j = 0; j < Ny; j++) {
                for (int i = 0; i < Nx; i++) {
                    int ip = (i+1) % Nx;
                    int im = (i-1+Nx) % Nx;
                    int jp = (j+1) % Ny;
                    int jm = (j-1+Ny) % Ny;
                    int kp = (k+1) % Nz;
                    int km = (k-1+Nz) % Nz;

                    double lap = (
                        w[IDX(ip,j,k,Nx,Ny)] + w[IDX(im,j,k,Nx,Ny)] +
                        w[IDX(i,jp,k,Nx,Ny)] + w[IDX(i,jm,k,Nx,Ny)] +
                        w[IDX(i,j,kp,Nx,Ny)] + w[IDX(i,j,km,Nx,Ny)] -
                        6.0 * w[IDX(i,j,k,Nx,Ny)]
                    ) / (h*h);

                    w_new[IDX(i,j,k,Nx,Ny)] = w[IDX(i,j,k,Nx,Ny)] + dt * nu * lap;
                }
            }
        }

        // Swap
        double *tmp = w; w = w_new; w_new = tmp;
    }

    free(w); free(w_new);

    return 0;
}
