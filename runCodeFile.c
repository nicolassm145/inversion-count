#include <stdio.h>
#include <stdlib.h>

// Declaração das funções
int* alocaVetor(int tamanho);
void leVetor(FILE *file, int *vetor, int tamanho);
int mergeCount(int *vetor, int *vetorTemp, int esquerda, int pivo, int direito);
int mergeSortCount(int *vetor, int *vetorTemp, int esquerda, int direito);
int contaInversoes(int *indices, int n);
int encontraComuns(int *lista1, int *lista2, int n1, int n2, int *indices);

int main() {
    int n1, n2;
    int *lista1, *lista2, *indices;
    int numComuns, inversoes;
    char filepath[] = "../test cases/7.in";

    FILE *file = fopen(filepath, "r");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    fscanf(file, "%d", &n1);
    lista1 = alocaVetor(n1);
    if (lista1 == NULL) {
        fclose(file);
        return 1;
    }
    leVetor(file, lista1, n1);  // Lê os elementos da primeira lista

    // Lê o tamanho da segunda lista e aloca espaço para ela
    fscanf(file, "%d", &n2);
    lista2 = alocaVetor(n2);
    if (lista2 == NULL) {
        free(lista1);  // Libera lista1 em caso de erro
        fclose(file);
        return 1;
    }
    leVetor(file, lista2, n2);  // Lê os elementos da segunda lista

    // Alocar memória para os índices dos elementos comuns entre as listas
    indices = alocaVetor(n1);
    if (indices == NULL) {
        free(lista1);
        free(lista2);
        fclose(file);
        return 1;
    }

    // Encontrar elementos comuns e armazenar seus índices de lista2 em indices
    numComuns = encontraComuns(lista1, lista2, n1, n2, indices);

    // Conta as inversões nos índices dos elementos comuns
    inversoes = (numComuns > 0) ? contaInversoes(indices, numComuns) : 0;
    printf("%d\n", inversoes);  // Imprime o número de inversões encontradas

    // Libera a memória alocada
    free(lista1);
    free(lista2);
    free(indices);
    fclose(file);

    return 0;
}

// Função para alocar um vetor de tamanho específico
int* alocaVetor(int tamanho) {
    int *vetor = malloc(tamanho * sizeof(int));
    if (vetor == NULL) {
        perror("Erro ao alocar memória");  // Mensagem de erro em caso de falha
    }
    return vetor;
}

// Função para ler um vetor de inteiros de um arquivo
void leVetor(FILE *file, int *vetor, int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        fscanf(file, "%d", &vetor[i]);  // Lê cada elemento e o armazena no vetor
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
            vetorTemp[k++] = vetor[i++];  // Elemento já ordenado
        } else {
            vetorTemp[k++] = vetor[j++];  // Conta a inversão
            inv_count += (pivo - i);      // Incrementa inversões
        }
    }

    // Copia o restante da sublista esquerda
    while (i <= pivo - 1)
        vetorTemp[k++] = vetor[i++];

    // Copia o restante da sublista direita
    while (j <= direito)
        vetorTemp[k++] = vetor[j++];

    // Copia os elementos ordenados de volta para o vetor original
    for (i = esquerda; i <= direito; i++)
        vetor[i] = vetorTemp[i];

    return inv_count;
}

// Função que implementa o merge sort e conta inversões
int mergeSortCount(int *vetor, int *vetorTemp, int esquerda, int direito) {
    int numInversoes = 0;
    if (direito > esquerda) {
        int pivo;
        pivo = (direito + esquerda) / 2;

        // Conta inversões na sublista esquerda
        numInversoes += mergeSortCount(vetor, vetorTemp, esquerda, pivo);
        // Conta inversões na sublista direita
        numInversoes += mergeSortCount(vetor, vetorTemp, pivo + 1, direito);

        // Conta inversões entre as sublistas
        numInversoes += mergeCount(vetor, vetorTemp, esquerda, pivo + 1, direito);
    }
    return numInversoes;
}

// Função para contar o número de inversões no vetor de índices
int contaInversoes(int *indices, int n) {
    int* vetorTemp = (int*)malloc(n * sizeof(int));
    if (vetorTemp == NULL) {
        perror("Erro ao alocar memória");  // Exibe erro caso a alocação falhe
        exit(1);
    }

    int resultado = mergeSortCount(indices, vetorTemp, 0, n - 1);
    free(vetorTemp);  // Libera memória temporária após uso
    return resultado;
}

// Função para encontrar elementos comuns entre duas listas
int encontraComuns(int *lista1, int *lista2, int n1, int n2, int indices[]) {
    int numComuns = 0;
    for (int i = 0; i < n1; i++) {
        for (int j = 0; j < n2; j++) {
            if (lista1[i] == lista2[j]) {
                indices[numComuns++] = j;  // Armazena o índice do elemento comum
                break;  // Evita duplicatas
            }
        }
    }
    return numComuns;  // Retorna o número de elementos comuns encontrados
}
