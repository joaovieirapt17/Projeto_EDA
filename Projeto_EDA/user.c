#define _CRT_SECURE_NO_WARNINGS

#include "user.h"
#include "string.h"

int add_user(NODE** start, USER* user) {
    USER* result = find_user_by_username(*start, user->username);
    if (result != NULL) return -1;
    return push(start, user, sizeof(USER));
}

USER* find_user_by_username(NODE* start, char username[100]) {
    NODE* aux = NULL;
    USER* user = NULL;

    if (isEmpty(&start)) return NULL;

    aux = start;
    while (aux != NULL) {
        user = (USER*)aux->data;

        if (strcmp(user->username, username) == 0) {
            return user;
        }

        aux = aux->next;
    }

    return NULL;
}

int remove_user_by_username(NODE** start, char username[100]) {
    NODE* aux = NULL;
    USER* user = NULL;
    int index = 0;

    if (isEmpty(start)) return -2;

    aux = *start;
    while (aux != NULL) {
        user = (USER*)aux->data;

        if (strcmp(user->username, username) == 0) {
            return splice(start, index);
        }

        aux = aux->next;
        index++;
    }

    return -1;
}

USER* login(NODE* start, char username[100], char password[100]) {
    USER* user = find_user_by_username(start, username);

    if (user == NULL) return NULL;

    if (strcmp(user->password, password) == 0) {
        return user;
    }

    return NULL;
}

int save_user(NODE* start) {
    NODE* aux = NULL;
    int res;

    remove("utilizadores.dat"); //Remove o ficheiro binário, caso ele já exista

    aux = start;
    while (aux != NULL) {
        res = appendToFile("utilizadores.dat", aux->data, sizeof(USER));

        if (res != 0) {
            return -1;
        }

        aux = aux->next;
    }

    return 0;
}

int save_user_txt(NODE* start) {
    NODE* aux = NULL;
    USER* user = NULL;

    FILE* fp = fopen("utilizadores.txt", "w");

    if (fp == NULL) return -3;

    aux = start;
    while (aux != NULL) {
        user = (USER*)aux->data;

        fprintf(fp, "----- UTILIZADOR -----\n");
        fprintf(fp, "Username: %s\n", user->username);
        fprintf(fp, "Nome: %s\n", user->nome);
        fprintf(fp, "Email: %s\n", user->email);
        fprintf(fp, "NIF: %d\n", user->NIF);
        fprintf(fp, "Saldo: %.2f\n", user->saldo);
        fprintf(fp, "Role: %d\n", user->role);

        aux = aux->next;
    }

    fclose(fp);
    return 0;
}


int load_users(NODE** start) {
    int res;

    FILE* fp = fopen("utilizadores.dat", "rb");

    if (fp == NULL) return -3;

    do {
        USER* user = (USER*)malloc(sizeof(USER));

        res = fread(user, sizeof(USER), 1, fp);

        // Nao leu nenhum utilizador, sai do loop
        if (res == 0) break;

        add_user(start, user);
    } while (1);

    fclose(fp);

    return 0;
}

int guardar_users(NODE* start) {
    save_user(start);
    save_user_txt(start);
}