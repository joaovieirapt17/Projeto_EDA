/**
 * @file lista_ligada.h
 * @brief Definição e implementação de uma lista ligada genérica.
 *
 * Este ficheiro contém a definição e implementação de uma lista ligada genérica.
 * Cada elemento da lista é representado por um ponteiro genérico void* que pode ser
 * utilizado para armazenar qualquer tipo de dado.
 */

#define _CRT_SECURE_NO_WARNINGS

#pragma once
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Estrutura que representa um nó da lista ligada.
 */
typedef struct node {
    struct node* next; // Ponteiro para o próximo nó da lista
    void* data; //Ponteiro genérico para o dado armazenado no nó
}NODE;

/**
 * @brief Adiciona um elemento no final da lista ligada.
 * @param start Ponteiro para o ponteiro do primeiro nó da lista.
 * @param data Ponteiro para o dado a ser adicionado na lista.
 * @param size Tamanho do dado em bytes.
 * @return 0 se a operação for bem sucedida, -3 se ocorrer falta de memória.
 */
int push(NODE** start, void* data, size_t size);

/**
 * @brief Remove o último elemento da lista ligada.
 * @param start Ponteiro para o ponteiro do primeiro nó da lista.
 * @return 0 se a operação for bem-sucedida, -2 se a lista estiver vazia.
 */
int pop(NODE** start);

/**
 * @brief Adiciona um elemento no início da lista ligada.
 * @param start Ponteiro para o ponteiro do primeiro nó da lista.
 * @param data Ponteiro para o dado a ser adicionado na lista.
 * @param size Tamanho do dado em bytes.
 * @return 0 se a operação for bem sucedida, -3 se ocorrer falta de memória.
 */
int unshift(NODE** start, void* data, size_t size);

/**
 * @brief Remove o primeiro elemento da lista ligada.
 * @param start Ponteiro para o ponteiro do primeiro nó da lista.
 * @return 0 se a operação for bem sucedida, -2 se a lista estiver vazia.
 */
int shift(NODE** start);

/**
 * @brief Remove um elemento da lista ligada dado o seu índice.
 * @param start Ponteiro para o ponteiro do primeiro nó da lista.
 * @param index Índice do elemento a ser removido.
 * @return 0 se a operação for bem sucedida, -1 se o elemento não for encontrado,
 * -2 se a lista estiver vazia.
 */
int splice(NODE** start, int index);

/**
 * @brief Retorna o tamanho da lista ligada.
 * @param start Ponteiro para o primeiro nó da lista.
 * @return Tamanho da lista.
 */
int length(NODE* start);


/**
 * @brief Apaga todos os elementos da lista ligada.
 * @param start Ponteiro para o ponteiro do primeiro nó da lista.
 */
void clear(NODE** start);

/**
 * @brief Verifica se a lista ligada está vazia.
 * @param start Ponteiro para o início da lista.
 * @return Retorna 1 se a lista está vazia e 0 caso contrário.
 */
int isEmpty(NODE** start);

/**
 * @brief Retorna o último nó da lista ligada ou NULL.
 * @param start Ponteiro para o início da lista.
 * @return Retorna um ponteiro para o último nó da lista ou NULL se a lista estiver vazia.
 */
NODE* last_node(NODE* start);

/**
 * @brief Acrescenta dados ao ficheiro especificado.
 * @param filename Nome do ficheiro ao qual os dados serão acrescentados.
 * @param data Ponteiro para os dados que serão acrescentados.
 * @param size Tamanho dos dados que serão acrescentados.
 * @return Retorna 0 em caso de sucesso, -1 se não foi possível acrescentar os dados e -3 em caso de erro ao abrir o ficheiro.
 */
int appendToFile(char filename[100], void* data, size_t size);