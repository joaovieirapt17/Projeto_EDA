/**
 * @file user.h
 * @brief Este arquivo cont�m estruturas e fun��es relacionadas � manipula��o de utilizadores.
 */

#define _CRT_SECURE_NO_WARNINGS
#pragma once

#include "linkedlist.h"

 /**
  * @brief Representa a fun��o de um utilizador (Cliente ou Gestor).
  */
typedef enum role {
    cliente = 0,
    gestor = 1
}ROLE;

/**
 * @brief Estrutura que representa um utilizador.
 */
typedef struct user {
    char username[100];
    char password[100];
    char nome[100];
    char email[100];
    int NIF;
    float saldo;
    char morada[100];
    ROLE role;
}USER;

/**
 * @brief Adiciona um novo utilizador � lista.
 * @param start O ponteiro para o in�cio da lista.
 * @param user O ponteiro para o utilizador a ser adicionado.
 * @return 0 em caso de sucesso.
 * @return -1 se o nome de utilizador j� existir.
 * @return -3 se n�o houver mem�ria dispon�vel.
 */
int add_user(NODE** start, USER* user);

/**
 * @brief Remove um utilizador dado um nome de utilizador.
 * @param start O ponteiro para o in�cio da lista.
 * @param username O nome de utilizador do utilizador a ser removido.
 * @return 0 em caso de sucesso.
 * @return -1 se o utilizador n�o for encontrado.
 * @return -2 se a lista estiver vazia.
 */
int remove_user_by_username(NODE** start, char username[100]);

/**
 * @brief Encontra um utilizador dado um nome de utilizador.
 * @param start O ponteiro para o in�cio da lista.
 * @param username O nome de utilizador do utilizador a ser encontrado.
 * @return O ponteiro para o utilizador encontrado.
 * @return NULL se o utilizador n�o for encontrado.
 */
USER* find_user_by_username(NODE* start, char username[100]);

/**
 * @brief Efetua o login do utilizador dado um nome de utilizador e uma senha.
 * @param start O ponteiro para o in�cio da lista.
 * @param username O nome de utilizador do utilizador.
 * @param password A senha do utilizador.
 * @return O ponteiro para o utilizador que efetuou o login.
 * @return NULL se o utilizador n�o for encontrado.
 */
USER* login(NODE* start, char username[100], char password[100]);

/**
 * @brief Carrega os utilizadores a partir de um arquivo bin�rio.
 * @param start O ponteiro para o in�cio da lista.
 * @return 0 em caso de sucesso.
 * @return -3 se ocorrer um erro ao abrir o arquivo.
 */
int load_users(NODE** start);

int guardar_users(NODE* start);

int save_user(NODE* start);