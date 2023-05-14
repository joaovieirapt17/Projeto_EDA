#define _CRT_SECURE_NO_WARNINGS
#pragma once

#include "user.h"
#include <conio.h>
#include "meio.h"
#include "grafo.h"

void clear_menu();

void any_key();


int initial_menu(NODE* users, USER** auth);
int login_menu(NODE* users, USER** auth);
int menu_cliente(USER auth, NODE** users, NODE** meios);
int menu_gestor(USER auth, NODE** users, NODE** meios);
void menu_gerir_gestores(USER auth, NODE** users);
void menu_gerir_clientes(USER auth, NODE** users);
void menu_gerir_meios(USER auth, NODE** users, NODE** meios, NODE** vertices);


int criar_gestor(NODE** users);
int criar_cliente(NODE** users);
int criar_meio_e_vertice(NODE** meios, NODE** vertices);

void listar_gestores_registados(NODE* users);
void listar_clientes_registados(NODE* users);
void listar_meios_disponiveis_desc_autonomia(NODE* meios);
void listar_meios_vertice_geocode(NODE* vertices); 

void alterar_dados_gestor(NODE** users);
void alterar_dados_cliente(NODE** users);
void alterar_dados_meios(NODE** meios);
void alterar_dados_proprio_cliente(NODE** utilizadores, USER auth);

void listar_meios_geocode(NODE* meios);
void listar_meios_proximos(NODE* meios); 

void remover_cliente(NODE** utilizadores);
void remover_meio(NODE** meios);

void alugar_meio(NODE** meios, NODE** utilizadores, USER user);

void carregar_saldo(USER auth, NODE** utilizadores);



