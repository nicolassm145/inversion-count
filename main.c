#include <stdio.h>
#include <stdlib.h>
// Estrutura do hashmap para mapear posições de filmes
// Usando Hash como tentativa de otimizar o código
typedef struct {
    int *chaves;
    int *valores;
    int tamanho;
} HashMap;

// Declaração das funções
int *alocaVetor(int tamanho);
void leVetor(int *vetor, int tamanho);
HashMap *criarHashMap(int tamanho);
void inserirHashMap(HashMap *map, int chave, int valor);
int buscarHashMap(HashMap *map, int chave);
void liberarHashMap(HashMap *map);
int mergeCount(int *vetor, int *vetorTemp, int esquerda, int pivo, int direita);
int mergeSortCount(int *vetor, int *vetorTemp, int esquerda, int direita);
int contaInversoes(int *indices, int numComuns);
int encontraComuns(int *lista1, int *lista2, int n1, int n2, int *indices);

int main() {
    int n1, n2, numComuns, inversoes;
    int *lista1, *lista2, *indices;
    // Leitura dos tamanhos das listas e preenche os vetores com os filmes
    // Lista1
    scanf("%d", &n1);
    lista1 = alocaVetor(n1);
    leVetor(lista1, n1);
    // Lista2
    scanf("%d", &n2);
    lista2 = alocaVetor(n2);
    leVetor(lista2, n2);
    // Lista com os Indices
    indices = alocaVetor(n1);

    numComuns = encontraComuns(lista1, lista2, n1, n2, indices);
    inversoes = contaInversoes(indices, numComuns);
    printf("%d\n", inversoes);

    free(lista1);
    free(lista2);
    free(indices);
    return 0;
}

// Funções de alocação e armazenamento do vetor
int* alocaVetor(int tamanho) {
    int *vetor = malloc(tamanho * sizeof(int));
    if (!vetor)
        perror("Erro ao alocar memória");
    return vetor;
}

void leVetor(int *vetor, int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        scanf("%d", &vetor[i]);
    }
}

// Funções para o funcionamento do Hashmap
// Cria um novo hashmap
HashMap* criarHashMap(int tamanho) {
    HashMap *map = malloc(sizeof(HashMap));
    // Usa calloc para inicializar o array de chaves e valores com zero
    map->chaves = (int*)calloc(tamanho, sizeof(int));
    map->valores = (int*)calloc(tamanho, sizeof(int));
    map->tamanho = tamanho;
    return map;
}
// Insere um par (chave-valor) no hashmap
void inserirHashMap(HashMap *map, int chave, int valor) {
    int indice = chave % map->tamanho;                    // Calcula o índice inicial a partir da chave
    // Sondagem linear
    while (map->chaves[indice] != 0) {                    // Verifica se a posição está ocupada
        indice = (indice + 1) % map->tamanho;             // Avança até encontrar uma posição livre
    }
    map->chaves[indice] = chave;
    map->valores[indice] = valor;
}
// Busca um valor a partir de uma chave
int buscarHashMap(HashMap *map, int chave) {
    int indice = chave % map->tamanho;
    while (map->chaves[indice] != 0) {
        if (map->chaves[indice] == chave)
            return map->valores[indice];
        indice = (indice + 1) % map->tamanho;
    }
    return -1;                                            // Se a chave não foi encontrada no hashmap
}

void liberarHashMap(HashMap *map) {
    free(map->chaves);
    free(map->valores);
    free(map);
}
// Auxilia na contagem de inversões ao mesclar (merge) dois vetores
int mergeCount(int *vetor, int *vetorTemp, int esquerda, int pivo, int direita) {
    int i = esquerda;       // Índice inicial da esquerda
    int j = pivo;           // Índice inicial da direita
    int k = esquerda;       // Índice para o vetorTemp
    int inv_count = 0;
    // Combina os elementos das duas metades em vetorTemp
    while (i <= pivo - 1 && j <= direita) {
        if (vetor[i] <= vetor[j]) {
            vetorTemp[k++] = vetor[i++];
        } else {
            vetorTemp[k++] = vetor[j++];
            inv_count += (pivo - i);
        }
    }
    // Copia os elementos:
    // Metade esquerda
    while (i <= pivo - 1)
        vetorTemp[k++] = vetor[i++];
    // Metade direita
    while (j <= direita)
        vetorTemp[k++] = vetor[j++];
    // VetorTemp para o original.
    for (i = esquerda; i <= direita; i++)
        vetor[i] = vetorTemp[i];
    return inv_count;
}
// Ordena e conta as inversões do vetor.
int mergeSortCount(int *vetor, int *vetorTemp, int esquerda, int direita) {
    int pivo, inv_count = 0;
    if (direita > esquerda) {
        pivo = (direita + esquerda) / 2;
        // Conta as inversões na metade esquerda.
        inv_count += mergeSortCount(vetor, vetorTemp, esquerda, pivo);
        // Conta as inversões na metade direita.
        inv_count += mergeSortCount(vetor, vetorTemp, pivo + 1, direita);
        // Conta as inversões entre as duas metades.
        inv_count += mergeCount(vetor, vetorTemp, esquerda, pivo + 1, direita);
    }
    return inv_count;
}
// Conta inversões usando MergeSort
int contaInversoes(int *indices, int numComuns) {
    if (numComuns <= 0) // Caso não haja elementos em comum
        return 0;
    int* vetorTemp = malloc(numComuns * sizeof(int));
    int resultado = mergeSortCount(indices, vetorTemp, 0, numComuns - 1);
    free(vetorTemp);
    return resultado;
}
// Usando Hashmap, encontra elementos comuns entre as duas listas
int encontraComuns(int *lista1, int *lista2, int n1, int n2, int *indices) {
    HashMap *map = criarHashMap(n2 * 2);
    int numComuns = 0;
    // Armazena cada elemento da lista2 no hashmap
    for (int i = 0; i < n2; i++)
        inserirHashMap(map, lista2[i], i);
    // Percorre lista1 e busca cada elemento dentro do hashmap
    for (int i = 0; i < n1; i++) {
        int pos = buscarHashMap(map, lista1[i]);
        if (pos != -1)
            indices[numComuns++] = pos;
    }
    liberarHashMap(map);
    return numComuns;
}