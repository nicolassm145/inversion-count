#include <stdio.h>
#include <stdlib.h>

#define MAX 100000

// Função auxiliar para contar inversões em um merge
int merge_e_conta(int arr[], int temp[], int left, int mid, int right) {
    int i = left; // Índice para a sublista esquerda
    int j = mid;  // Índice para a sublista direita
    int k = left; // Índice para a lista ordenada
    int inv_count = 0;

    // Junta as duas sublistas e conta as inversões
    while ((i <= mid - 1) && (j <= right)) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
            inv_count += (mid - i); // Contagem de inversões
        }
    }

    while (i <= mid - 1)
        temp[k++] = arr[i++];

    while (j <= right)
        temp[k++] = arr[j++];

    for (i = left; i <= right; i++)
        arr[i] = temp[i];

    return inv_count;
}

// Função principal que implementa o merge sort e conta inversões
int mergeSort_e_conta(int arr[], int temp[], int left, int right) {
    int mid, inv_count = 0;
    if (right > left) {
        mid = (right + left) / 2;

        inv_count += mergeSort_e_conta(arr, temp, left, mid);
        inv_count += mergeSort_e_conta(arr, temp, mid + 1, right);

        inv_count += merge_e_conta(arr, temp, left, mid + 1, right);
    }
    return inv_count;
}

// Conta inversões entre índices em vez dos valores dos filmes
int conta_inversoes(int indices[], int n) {
    int* temp = (int*)malloc(n * sizeof(int));
    if (temp == NULL) {
        perror("Erro ao alocar memória");
        exit(1);
    }

    int resultado = mergeSort_e_conta(indices, temp, 0, n - 1);
    free(temp);
    return resultado;
}

// Função para ler o vetor a partir de um arquivo
void leVetor(FILE *file, int* vetor, int n) {
    for (int i = 0; i < n; i++) {
        fscanf(file, "%d", &vetor[i]);
    }
}

// Função para encontrar os filmes em comum entre as duas listas
int encontraComuns(int lista1[], int lista2[], int n1, int n2, int indices[]) {
    int numComuns = 0;
    for (int i = 0; i < n1; i++) {
        for (int j = 0; j < n2; j++) {
            if (lista1[i] == lista2[j]) {
                indices[numComuns++] = j;  // Armazena o índice da lista2
                break;  // Para evitar duplicados
            }
        }
    }
    return numComuns;
}

int main() {
    int n1, n2;
    int *lista1, *lista2, *indices;
    int numComuns = 0;
    char filepath[] = "../test cases/7.in";  // Caminho do arquivo

    // Abrir o arquivo
    FILE *file = fopen(filepath, "r");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    // Leitura do tamanho e dos elementos de cada lista
    fscanf(file, "%d", &n1);
    lista1 = (int*)malloc(n1 * sizeof(int));  // Alocação dinâmica para lista1
    if (lista1 == NULL) {
        perror("Erro ao alocar memória para lista1");
        return 1;
    }

    leVetor(file, lista1, n1);

    fscanf(file, "%d", &n2);
    lista2 = (int*)malloc(n2 * sizeof(int));  // Alocação dinâmica para lista2
    if (lista2 == NULL) {
        perror("Erro ao alocar memória para lista2");
        free(lista1);
        return 1;
    }

    leVetor(file, lista2, n2);

    // Alocar dinamicamente a memória para os índices
    indices = (int*)malloc(n1 * sizeof(int));  // No máximo n1 filmes comuns
    if (indices == NULL) {
        perror("Erro ao alocar memória para indices");
        free(lista1);
        free(lista2);
        return 1;
    }

    // Encontrar os filmes comuns e armazenar seus índices da lista2
    numComuns = encontraComuns(lista1, lista2, n1, n2, indices);

    // Se não houver filmes comuns, não há inversões
    if (numComuns == 0) {
        printf("0\n");
    } else {
        // Contar as inversões entre os índices dos filmes comuns
        int inversoes = conta_inversoes(indices, numComuns);
        printf("%d\n", inversoes);  // Imprime int
    }

    // Liberar memória alocada
    free(lista1);
    free(lista2);
    free(indices);

    // Fechar o arquivo
    fclose(file);

    return 0;
}
