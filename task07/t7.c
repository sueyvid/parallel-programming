#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

typedef struct Node {
    char filename[20];
    struct Node* next;
} Node;

int main() {
    // Criando lista encadeada fictícia
    Node n9 = {"file9.txt", NULL};
    Node n8 = {"file8.txt", &n9};
    Node n7 = {"file7.txt", &n8};
    Node n6 = {"file6.txt", &n7};
    Node n5 = {"file5.txt", &n6};
    Node n4 = {"file4.txt", &n5};
    Node n3 = {"file3.txt", &n4};
    Node n2 = {"file2.txt", &n3};
    Node n1 = {"file1.txt", &n2};
    Node* head = &n1;

    #pragma omp parallel
    {
        #pragma omp single
        {
            Node* current = head;
            while (current != NULL) {
                int criou = omp_get_thread_num();
                
                #pragma omp task
                {
                    printf("%s, Criou: %d, Exec: %d\n",
                           current->filename,
                           criou,
                           omp_get_thread_num());
                }
                current = current->next;
            }
        }
    }

    printf("Todas as tarefas concluídas!\n");
    return 0;
}
