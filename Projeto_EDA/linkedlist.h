/**
 * @file lista_ligada.h
 * @brief Defini��o e implementa��o de uma lista ligada gen�rica.
 *
 * Este ficheiro cont�m a defini��o e implementa��o de uma lista ligada gen�rica.
 * Cada elemento da lista � representado por um ponteiro gen�rico void* que pode ser
 * utilizado para armazenar qualquer tipo de dado.
 */

#define _CRT_SECURE_NO_WARNINGS

#pragma once
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Estrutura que representa um n� da lista ligada.
 */
typedef struct node {
    struct node* next; // Ponteiro para o pr�ximo n� da lista
    void* data; //Ponteiro gen�rico para o dado armazenado no n�
}NODE;

/**
 * @brief Adiciona um elemento no final da lista ligada.
 * @param start Ponteiro para o ponteiro do primeiro n� da lista.
 * @param data Ponteiro para o dado a ser adicionado na lista.
 * @param size Tamanho do dado em bytes.
 * @return 0 se a opera��o for bem sucedida, -3 se ocorrer falta de mem�ria.
 */
int push(NODE** start, void* data, size_t size);

/**
 * @brief Remove o �ltimo elemento da lista ligada.
 * @param start Ponteiro para o ponteiro do primeiro n� da lista.
 * @return 0 se a opera��o for bem-sucedida, -2 se a lista estiver vazia.
 */
int pop(NODE** start);

/**
 * @brief Adiciona um elemento no in�cio da lista ligada.
 * @param start Ponteiro para o ponteiro do primeiro n� da lista.
 * @param data Ponteiro para o dado a ser adicionado na lista.
 * @param size Tamanho do dado em bytes.
 * @return 0 se a opera��o for bem sucedida, -3 se ocorrer falta de mem�ria.
 */
int unshift(NODE** start, void* data, size_t size);

/**
 * @brief Remove o primeiro elemento da lista ligada.
 * @param start Ponteiro para o ponteiro do primeiro n� da lista.
 * @return 0 se a opera��o for bem sucedida, -2 se a lista estiver vazia.
 */
int shift(NODE** start);

/**
 * @brief Remove um elemento da lista ligada dado o seu �ndice.
 * @param start Ponteiro para o ponteiro do primeiro n� da lista.
 * @param index �ndice do elemento a ser removido.
 * @return 0 se a opera��o for bem sucedida, -1 se o elemento n�o for encontrado,
 * -2 se a lista estiver vazia.
 */
int splice(NODE** start, int index);

/**
 * @brief Retorna o tamanho da lista ligada.
 * @param start Ponteiro para o primeiro n� da lista.
 * @return Tamanho da lista.
 */
int length(NODE* start);


/**
 * @brief Apaga todos os elementos da lista ligada.
 * @param start Ponteiro para o ponteiro do primeiro n� da lista.
 */
void clear(NODE** start);

/**
 * @brief Verifica se a lista ligada est� vazia.
 * @param start Ponteiro para o in�cio da lista.
 * @return Retorna 1 se a lista est� vazia e 0 caso contr�rio.
 */
int isEmpty(NODE** start);

/**
 * @brief Retorna o �ltimo n� da lista ligada ou NULL.
 * @param start Ponteiro para o in�cio da lista.
 * @return Retorna um ponteiro para o �ltimo n� da lista ou NULL se a lista estiver vazia.
 */
NODE* last_node(NODE* start);

/**
 * @brief Acrescenta dados ao ficheiro especificado.
 * @param filename Nome do ficheiro ao qual os dados ser�o acrescentados.
 * @param data Ponteiro para os dados que ser�o acrescentados.
 * @param size Tamanho dos dados que ser�o acrescentados.
 * @return Retorna 0 em caso de sucesso, -1 se n�o foi poss�vel acrescentar os dados e -3 em caso de erro ao abrir o ficheiro.
 */
int appendToFile(char filename[100], void* data, size_t size);