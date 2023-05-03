#define _CRT_SECURE_NO_WARNINGS

#pragma once
#include "linkedlist.h"

typedef enum role {
    cliente = 0,
    gestor = 1
}ROLE;

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


/*
 * Adiciona um novo utilizador
 *  - return  0: Success
 *  - return -1: Username already exists
 *  - return -3: Out of memory
*/
int add_user(NODE** start, USER* user);

/*
 * Remove um utilizador dado um respetivo nome
 *  - return  0: Success
 *  - return -1: User not found
 *  - return -2: List is empty
*/
int remove_user_by_username(NODE** start, char username[100]);

/*
 * Encontra um utilizador dado um respetivo nome
 *  - Returns the user
 *  - Returns NULL if not found
*/
USER* find_user_by_username(NODE* start, char username[100]);

/*
 * Login do utilizador dado um username e password
 *  - Returns the user
 *  - Returns NULL if not found
*/
USER* login(NODE* start, char username[100], char password[100]);

int save_user(NODE* start);

int load_users(NODE** start);

int guardar_users(NODE* start);