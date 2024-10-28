
---

# Sistema de Recomendação de filmes 

Este projeto implementa uma solução eficiente para contar o número de inversões entre duas listas de filmes favoritos, utilizando a combinação de **HashMap** para otimização e o algoritmo de **Merge Sort** para contagem de inversões. O projeto foi desenvolvido como parte do **Trabalho 02** da disciplina **CTCO04 - Projeto e Análise de Algoritmos**.

## Objetivos

- Implementar uma função que utilize **HashMap** para encontrar elementos comuns entre duas listas de filmes.
- Contar o número de inversões nas posições dos filmes comuns, usando o algoritmo de **Merge Sort**.
- Demonstrar a aplicação de técnicas de programação eficientes para resolver problemas práticos envolvendo listas.

## Contagem de Inversões

O conceito de **inversão** em uma lista é definido como um par de índices `(i, j)` tal que `i < j` e `A[i] > A[j]`. O projeto conta quantas dessas inversões existem nas posições dos filmes que estão presentes em ambas as listas. A contagem de inversões é útil em várias aplicações, incluindo análise de dados e comparação de ordens.

### Algoritmo de Merge Sort

O Merge Sort é um algoritmo de ordenação eficiente com complexidade de tempo O(n log n), que utiliza a técnica de **divisão e conquista**. Para contar as inversões, o algoritmo é modificado para registrar quantas inversões ocorrem durante o processo de mesclagem das sublistas.

## Estrutura do Projeto

- **HashMap**: Utilizado para armazenar a posição dos filmes em uma das listas, permitindo busca rápida ao verificar a presença dos filmes na outra lista.
- **Contagem de Inversões**: O Merge Sort é adaptado para contar inversões enquanto ordena as listas de filmes comuns.
- **Leitura de Listas**: As listas de filmes são lidas a partir da entrada padrão, e a contagem de inversões é impressa como saída.

## Execução

O programa deve ser executado fornecendo as duas listas de filmes como entrada. Após a execução, a contagem de inversões será exibida na saída padrão.

### Exemplo de Entrada
```
4
42 25 48 63
4
48 25 95 42
```

### Exemplo de Saída
```
3
```

## Considerações Finais

Este projeto demonstra como a combinação de estruturas de dados (como HashMap) e algoritmos eficientes (como Merge Sort) pode ser utilizada para resolver problemas práticos de forma otimizada. A contagem de inversões é uma métrica importante em análises de dados e este trabalho explora sua aplicação em um contexto de listas de filmes.

---
