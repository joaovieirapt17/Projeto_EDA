#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include "user.h"
#include "menu.h"
#include "linkedlist.h"


int load(NODE** utilizadores, NODE** vertices) {
    load_users(utilizadores);
    load_vertices(vertices); 

    // Em caso de nao haver nenhum utilizador, é criado o utilizador root que é gestor
    if (length(*utilizadores) == 0) {
        USER root = { "root","root","root","root@root.com",0, 0, "",1 };
        USER* data = (USER*)malloc(sizeof(USER));

        if (data != NULL) {
            *data = root;
            add_user(utilizadores, data);
            save_user(*utilizadores);
        }
    }
}

int main() {
    int res = 0;
    NODE* utilizadores = NULL; //Lista para guardar utilizadores
    USER* auth = NULL; 
    NODE* vertices = NULL; //Lista para guardar meios dentro de cada vértice

    load(&utilizadores, &vertices);

    do {
        if (initial_menu(utilizadores, &auth) == -1) return 0;

        if (auth->role == 0) {
            res = menu_cliente(*auth, &utilizadores, &vertices);
        }
        else {
            res = menu_gestor(*auth, &utilizadores, &vertices);
        }

    } while (res == -4);

    printf("A sair...");

    return 0;
   
}

