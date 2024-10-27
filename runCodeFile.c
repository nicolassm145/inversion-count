#include <stdio.h>
#include <stdlib.h>

// Estrutura do hashmap para mapear posições de filmes
typedef struct {
    int *keys;
    int *values;
    int size;
} HashMap;

// Declaração das funções
int* alocaVetor(int tamanho);
void leVetor(int *vetor, int tamanho);
HashMap* criarHashMap(int tamanho);
void inserirHashMap(HashMap *map, int key, int value);
int buscarHashMap(HashMap *map, int key);
void liberarHashMap(HashMap *map);
int mergeCount(int *vetor, int *vetorTemp, int esquerda, int pivo, int direito);
int mergeSortCount(int *vetor, int *vetorTemp, int esquerda, int direito);
int contaInversoes(int *indices, int n);
int encontraComuns(int *lista1, int *lista2, int n1, int n2, int *indices);

int main() {
    int n1, n2, numComuns, inversoes;
    int *lista1, *lista2, *indices;

    scanf("%d", &n1);
    lista1 = alocaVetor(n1);
    if (!lista1) return 1;
    leVetor(lista1, n1);

    scanf("%d", &n2);
    lista2 = alocaVetor(n2);
    if (!lista2) {
        free(lista1);
        return 1;
    }
    leVetor(lista2, n2);

    indices = alocaVetor(n1);
    if (!indices) {
        free(lista1);
        free(lista2);
        return 1;
    }

    numComuns = encontraComuns(lista1, lista2, n1, n2, indices);
    inversoes = (numComuns > 0) ? contaInversoes(indices, numComuns) : 0;
    printf("%d\n", inversoes);

    free(lista1);
    free(lista2);
    free(indices);
    return 0;
}

// Funções

int* alocaVetor(int tamanho) {
    int *vetor = malloc(tamanho * sizeof(int));
    if (!vetor) perror("Erro ao alocar memória");
    return vetor;
}

void leVetor(int *vetor, int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        scanf("%d", &vetor[i]);
    }
}

HashMap* criarHashMap(int tamanho) {
    HashMap *map = (HashMap*)malloc(sizeof(HashMap));
    map->keys = (int*)calloc(tamanho, sizeof(int));
    map->values = (int*)calloc(tamanho, sizeof(int));
    map->size = tamanho;
    return map;
}

void inserirHashMap(HashMap *map, int key, int value) {
    int index = key % map->size;
    while (map->keys[index] != 0) {
        index = (index + 1) % map->size;
    }
    map->keys[index] = key;
    map->values[index] = value;
}

int buscarHashMap(HashMap *map, int key) {
    int index = key % map->size;
    while (map->keys[index] != 0) {
        if (map->keys[index] == key)
            return map->values[index];
        index = (index + 1) % map->size;
    }
    return -1;
}

void liberarHashMap(HashMap *map) {
    free(map->keys);
    free(map->values);
    free(map);
}

int mergeCount(int *vetor, int *vetorTemp, int esquerda, int pivo, int direito) {
    int i = esquerda, j = pivo, k = esquerda;
    int inv_count = 0;

    while (i <= pivo - 1 && j <= direito) {
        if (vetor[i] <= vetor[j]) {
            vetorTemp[k++] = vetor[i++];
        } else {
            vetorTemp[k++] = vetor[j++];
            inv_count += (pivo - i);
        }
    }
    while (i <= pivo - 1) vetorTemp[k++] = vetor[i++];
    while (j <= direito) vetorTemp[k++] = vetor[j++];
    for (i = esquerda; i <= direito; i++) vetor[i] = vetorTemp[i];

    return inv_count;
}

int mergeSortCount(int *vetor, int *vetorTemp, int esquerda, int direito) {
    int pivo, inv_count = 0;
    if (direito > esquerda) {
        pivo = (direito + esquerda) / 2;
        inv_count += mergeSortCount(vetor, vetorTemp, esquerda, pivo);
        inv_count += mergeSortCount(vetor, vetorTemp, pivo + 1, direito);
        inv_count += mergeCount(vetor, vetorTemp, esquerda, pivo + 1, direito);
    }
    return inv_count;
}

int contaInversoes(int *indices, int n) {
    int* vetorTemp = malloc(n * sizeof(int));
    if (!vetorTemp) {
        perror("Erro ao alocar memória");
        exit(1);
    }
    int resultado = mergeSortCount(indices, vetorTemp, 0, n - 1);
    free(vetorTemp);
    return resultado;
}

int encontraComuns(int *lista1, int *lista2, int n1, int n2, int *indices) {
    HashMap *map = criarHashMap(n2 * 2);
    for (int i = 0; i < n2; i++) {
        inserirHashMap(map, lista2[i], i);
    }

    int numComuns = 0;
    for (int i = 0; i < n1; i++) {
        int pos = buscarHashMap(map, lista1[i]);
        if (pos != -1) {
            indices[numComuns++] = pos;
        }
    }

    liberarHashMap(map);
    return numComuns;
}
