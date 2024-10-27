#include <stdio.h>
#include <stdlib.h>

// Declaração das funções
int* alocaVetor(int tamanho);
void leVetor(int *vetor, int tamanho);
int mergeCount(int *vetor, int *vetorTemp, int esquerda, int pivo, int direito);
int mergeSortCount(int *vetor, int *vetorTemp, int esquerda, int direito);
int contaInversoes(int *indices, int n);
int encontraComuns(int *lista1, int *lista2, int n1, int n2, int *indices);

int main() {
    int n1, n2;
    int *lista1, *lista2, *indices;
    int numComuns, inversoes;

    scanf("%d", &n1);
    lista1 = alocaVetor(n1);
    if (lista1 == NULL) {
        return 1;
    }
    leVetor(lista1, n1);

    scanf("%d", &n2);
    lista2 = alocaVetor(n2);
    if (lista2 == NULL) {
        free(lista1);
        return 1;
    }
    leVetor(lista2, n2);

    indices = alocaVetor(n1);
    if (indices == NULL) {
        free(lista1);
        free(lista2);
        return 1;
    }

    numComuns = encontraComuns(lista1, lista2, n1, n2, indices);
    if (numComuns > 0)
        inversoes = contaInversoes(indices, numComuns);
    else
        inversoes = 0;
    printf("%d\n", inversoes);

    free(lista1);
    free(lista2);
    free(indices);
    return 0;
}

// Funções
int* alocaVetor(int tamanho) {
    int *vetor = malloc(tamanho * sizeof(int));
    if (vetor == NULL) {
        perror("Erro ao alocar memória");
    }
    return vetor;
}

void leVetor(int *vetor, int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        scanf("%d", &vetor[i]);
    }
}

// Função auxiliar para contar inversões durante o merge
int mergeCount(int *vetor, int *vetorTemp, int esquerda, int pivo, int direito) {
    int i = esquerda;   // Índice para a sublista esquerda
    int j = pivo;       // Índice para a sublista direita
    int k = esquerda;   // Índice para a lista temporária ordenada
    int inv_count = 0;

    // Junta as duas sublistas e conta as inversões
    while (i <= pivo - 1 && j <= direito) {
        if (vetor[i] <= vetor[j]) {
            vetorTemp[k++] = vetor[i++];
        } else {
            vetorTemp[k++] = vetor[j++];
            inv_count += (pivo - i);
        }
    }
    while (i <= pivo - 1)
        vetorTemp[k++] = vetor[i++];
    while (j <= direito)
        vetorTemp[k++] = vetor[j++];
    for (i = esquerda; i <= direito; i++)
        vetor[i] = vetorTemp[i];

    return inv_count;
}

// Função do merge sort e conta inversões
int mergeSortCount(int *vetor, int *vetorTemp, int esquerda, int direito) {
    int pivo, inv_count = 0;
    if (direito > esquerda) {
        pivo = (direito + esquerda) / 2;
        // Conta inversões na sublista esquerda
        inv_count += mergeSortCount(vetor, vetorTemp, esquerda, pivo);
        // Conta inversões na sublista direita
        inv_count += mergeSortCount(vetor, vetorTemp, pivo + 1, direito);
        // Conta inversões entre as sublistas
        inv_count += mergeCount(vetor, vetorTemp, esquerda, pivo + 1, direito);
    }
    return inv_count;
}

// Função para contar o número de inversões no vetor de índices
int contaInversoes(int *indices, int n) {
    int* vetorTemp = malloc(n * sizeof(int));
    if (vetorTemp == NULL) {
        perror("Erro ao alocar memória");
        exit(1);
    }
    int resultado = mergeSortCount(indices, vetorTemp, 0, n - 1);
    free(vetorTemp);
    return resultado;
}

// Função para encontrar elementos comuns entre duas listas
int encontraComuns(int *lista1, int *lista2, int n1, int n2, int indices[]) {
    int numComuns = 0;
    for (int i = 0; i < n1; i++) {
        for (int j = 0; j < n2; j++) {
            if (lista1[i] == lista2[j]) {
                indices[numComuns++] = j;  // Armazena o índice
                break;  // Evita duplicatas
            }
        }
    }
    return numComuns;
}
