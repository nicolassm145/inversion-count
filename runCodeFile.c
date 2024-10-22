#include <stdio.h>
#include <stdlib.h>

int *alocaVetor(int tam);
void leVetor(FILE *file, int *vet, int tam);

int main() {
    int tam1, tam2;
    int numComuns = 0;
    char filepath[] = "../test cases/7.in";


    FILE *file = fopen(filepath, "r");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    fscanf(file, "%d", &tam1);
    fscanf(file, "%d", &tam2);

    // Aloca memória e preenche as listas 1 e 2
    int *lista1 = alocaVetor(tam1);
    leVetor(file, lista1, tam1);
    int *lista2 = alocaVetor(tam2);
    leVetor(file, lista2, tam2);

    int *indices = alocaVetor(tam1);

    free(lista1);
    free(lista2);
    free(indices);

    fclose(file);
    return 0;
}

// Funções
int *alocaVetor(int tam) {
    int *vet = malloc(tam * sizeof(int));
    if (vet == NULL) {
        perror("Erro ao alocar memória");
        free(vet);
        return 1;
    }
    return vet;
}

void leVetor(FILE *file, int *vet, int tam) {
    for (int i = 0; i < tam; i++) {
        fscanf(file, "%d", &vet[i]);
    }
}