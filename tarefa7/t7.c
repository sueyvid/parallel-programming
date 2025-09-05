#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>

// Estrutura do nó
typedef struct No {
    char nome_pokemon[100];
    struct No* prox;
} No;

// Função para criar novo nó
No* criar_no(const char* nome) {
    No* novo = (No*)malloc(sizeof(No));
    if (novo == NULL) {
        perror("Erro ao alocar memória");
        exit(1);
    }
    strncpy(novo->nome_pokemon, nome, sizeof(novo->nome_pokemon));
    novo->nome_pokemon[sizeof(novo->nome_pokemon) - 1] = '\0';
    novo->prox = NULL;
    return novo;
}

// Inserir no final da lista
void inserir(No** inicio, const char* nome) {
    No* novo = criar_no(nome);
    if (*inicio == NULL) {
        *inicio = novo;
    } else {
        No* temp = *inicio;
        while (temp->prox != NULL) {
            temp = temp->prox;
        }
        temp->prox = novo;
    }
}

// Liberar memória
void liberar_lista(No* inicio) {
    while (inicio != NULL) {
        No* temp = inicio;
        inicio = inicio->prox;
        free(temp);
    }
}

int main() {
    No* lista = NULL;

    // Arquivos fictícios
    inserir(&lista, "Bulbasaur");
    inserir(&lista, "Ivysaur");
    inserir(&lista, "Venusaur");
    inserir(&lista, "Charmander");
    inserir(&lista, "Charmeleon");
    inserir(&lista, "Charizard");
    inserir(&lista, "Squirtle");
    inserir(&lista, "Wartortle");
    inserir(&lista, "Blastoise");
    inserir(&lista, "Caterpie");
    inserir(&lista, "Metapod");
    inserir(&lista, "Butterfree");
    inserir(&lista, "Weedle");
    inserir(&lista, "Kakuna");
    inserir(&lista, "Beedrill");
    inserir(&lista, "Pidgey");
    inserir(&lista, "Pidgeotto");
    inserir(&lista, "Pidgeot");
    inserir(&lista, "Rattata");
    inserir(&lista, "Raticate");
    inserir(&lista, "Pikachu");
    inserir(&lista, "Raichu");
    inserir(&lista, "Jigglypuff");
    inserir(&lista, "Meowth");
    inserir(&lista, "Psyduck");
    inserir(&lista, "Machop");
    inserir(&lista, "Machoke");
    inserir(&lista, "Machamp");
    inserir(&lista, "Geodude");
    inserir(&lista, "Gengar");

    // Região paralela
    #pragma omp parallel
    {
        #pragma omp single
        {
            No* atual = lista;
            while (atual != NULL) {
                int criadora = omp_get_thread_num(); // thread que cria a tarefa

                #pragma omp task firstprivate(atual, criadora)
                {
                    int executora = omp_get_thread_num(); // thread que executa a tarefa
                    printf("Pokemon: %-12s | Criada por: %d | Executada por: %d\n",
                           atual->nome_pokemon, criadora, executora);
                }

                atual = atual->prox;
            }
        } // sincroniza as tasks no fim
    }

    liberar_lista(lista);
    return 0;
}
