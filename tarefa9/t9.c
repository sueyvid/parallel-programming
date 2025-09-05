#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

// Estrutura da lista encadeada
typedef struct No {
    int valor;
    struct No* prox;
} No;

// Cria um novo nó
No* criar_no(int valor) {
    No* novo = (No*) malloc(sizeof(No));
    if (!novo) {
        perror("Erro ao alocar nó");
        exit(1);
    }
    novo->valor = valor;
    novo->prox = NULL;
    return novo;
}

// Insere no início da lista
void inserir(No** lista, No* novo) {
    novo->prox = *lista;
    *lista = novo;
}

// Libera memória da lista
void liberar_lista(No* lista) {
    No* atual = lista;
    while (atual) {
        No* temp = atual;
        atual = atual->prox;
        free(temp);
    }
}

// Imprime a lista
void imprimir_lista(No* lista, const char* nome) {
    printf("%s: ", nome);
    No* atual = lista;
    while (atual) {
        printf("%d -> ", atual->valor);
        atual = atual->prox;
    }
    printf("NULL\n");
}

#define N 20  // número de inserções

int main() {
    srand(time(NULL));

    printf("=== Versão com 2 listas e regiões críticas nomeadas ===\n");

    No* lista1 = NULL;
    No* lista2 = NULL;

    #pragma omp parallel
    {
        #pragma omp single
        {
            for (int i = 0; i < N; i++) {
                #pragma omp task
                {
                    int valor = rand() % 1000;
                    int escolha = rand() % 2; // escolhe entre lista1 e lista2

                    if (escolha == 0) {
                        #pragma omp critical(lista1) // região crítica nomeada
                        inserir(&lista1, criar_no(valor));
                    } else {
                        #pragma omp critical(lista2) // outra região crítica independente
                        inserir(&lista2, criar_no(valor));
                    }
                }
            }
        }
    }

    imprimir_lista(lista1, "Lista 1");
    imprimir_lista(lista2, "Lista 2");

    liberar_lista(lista1);
    liberar_lista(lista2);

    printf("\n=== Versão generalizada (M listas) com locks explícitos ===\n");

    // int M = 4; // número de listas escolhido pelo usuário
    int M;
    printf("Digite o número de listas: ");
    scanf("%d", &M);

    No** listas = (No**) calloc(M, sizeof(No*));
    omp_lock_t* locks = (omp_lock_t*) malloc(M * sizeof(omp_lock_t));

    for (int i = 0; i < M; i++) {
        omp_init_lock(&locks[i]);
        listas[i] = NULL;
    }

    #pragma omp parallel
    {
        #pragma omp single
        {
            for (int i = 0; i < N; i++) {
                #pragma omp task
                {
                    int valor = rand() % 1000;
                    int escolha = rand() % M;

                    omp_set_lock(&locks[escolha]);
                    inserir(&listas[escolha], criar_no(valor));
                    omp_unset_lock(&locks[escolha]);
                }
            }
        }
    }

    for (int i = 0; i < M; i++) {
        char nome[32];
        sprintf(nome, "Lista %d", i);
        imprimir_lista(listas[i], nome);
        liberar_lista(listas[i]);
        omp_destroy_lock(&locks[i]);
    }

    free(listas);
    free(locks);

    return 0;
}
