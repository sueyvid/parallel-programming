#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <omp.h>

#define IDX(i,j,k,Nx,Ny) (((k)*(Ny)*(Nx)) + ((j)*(Nx)) + (i))

/* Retorna 1 se s representa um inteiro (apenas dígitos, opcionalmente com + ou - no início) */
static int is_integer_string(const char *s) {
    if (!s || *s == '\0') return 0;
    const char *p = s;
    if (*p == '+' || *p == '-') p++;
    if (*p == '\0') return 0;
    for (; *p; p++) if (!isdigit((unsigned char)*p)) return 0;
    return 1;
}

/* Retorna o primeiro token (antes da vírgula) de uma string (cópia alocada) */
static char *first_token_before_comma(const char *s) {
    if (!s) return NULL;
    char *dup = strdup(s);
    if (!dup) return NULL;
    char *comma = strchr(dup, ',');
    if (comma) *comma = '\0';
    return dup; // caller deve free()
}

int main(int argc, char *argv[]) {
    /* Parâmetros padrão */
    int Nx = 100, Ny = 100, Nz = 100;
    int steps = 1000;        /* será override por -i ou por argumento posicional */
    int num_threads = 0;     /* se >0, força omp_set_num_threads */
    double nu = 0.01;
    double dt = 0.0005;
    double h = 1.0 / Nx;

    /* --- Leitura dos argumentos de linha de comando --- */
    for (int ai = 1; ai < argc; ai++) {
        if ((strcmp(argv[ai], "-i") == 0 || strcmp(argv[ai], "--ipts") == 0) && ai + 1 < argc) {
            char *tok = first_token_before_comma(argv[ai + 1]);
            if (tok && is_integer_string(tok)) steps = atoi(tok);
            free(tok);
            ai++; /* pula valor */
        }
        else if ((strcmp(argv[ai], "-c") == 0 || strcmp(argv[ai], "--cores") == 0) && ai + 1 < argc) {
            char *tok = first_token_before_comma(argv[ai + 1]);
            if (tok && is_integer_string(tok)) num_threads = atoi(tok);
            free(tok);
            ai++;
        }
        else if (argv[ai][0] != '-') {
            /* argumento posicional (ex.: ./t12 320) -> considera como steps */
            if (is_integer_string(argv[ai])) {
                steps = atoi(argv[ai]);
            }
        }
        /* outros flags podem ser adicionados aqui se necessário */
    }

    /* Se o usuário indicou -c, força número de threads */
    if (num_threads > 0) {
        omp_set_num_threads(num_threads);
    }

    /* --- gravação simples para verificação (arquivo) --- */
    FILE *fout = fopen("saida.txt", "a");
    if (fout) {
        fprintf(fout, "steps=%d\n", steps);
        if (num_threads > 0) fprintf(fout, "threads_forcadas=%d\n", num_threads);
        else fprintf(fout, "threads_forcadas=0\n"); /* 0 indica uso de OMP_NUM_THREADS ou padrão */
        fclose(fout);
    } /* se falhar ao abrir, seguimos sem travar (mensagens iriam para slurm-<jobid>.out) */

    /* --- Alocação e simulação --- */
    int N = Nx * Ny * Nz;
    double *w = calloc((size_t)N, sizeof(double));
    double *w_new = calloc((size_t)N, sizeof(double));
    if (!w || !w_new) {
        fprintf(stderr, "Erro: falha na alocação de memória.\n");
        free(w); free(w_new);
        return 1;
    }

    /* Perturbação inicial */
    int ic = Nx/2, jc = Ny/2, kc = Nz/2;
    w[IDX(ic,jc,kc,Nx,Ny)] = 1.0;

    for (int n = 0; n < steps; n++) {
#pragma omp parallel for collapse(3) schedule(dynamic, 20)
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

        /* swap */
        double *tmp = w; w = w_new; w_new = tmp;
    }

    free(w); free(w_new);
    return 0;
}
