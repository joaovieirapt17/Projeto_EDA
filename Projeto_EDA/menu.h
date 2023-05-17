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
int menu_gestor(USER auth, NODE** users, NODE** meios, NODE** vertices);
void menu_gerir_gestores(USER auth, NODE** users);
void menu_gerir_clientes(USER auth, NODE** users);
void menu_gerir_meios(USER auth, NODE** users, NODE** meios, NODE** vertices);
int menu_gerir_grafo(USER auth, NODE** utilizadores, NODE** vertices); 


int criar_gestor(NODE** users);
int criar_cliente(NODE** users);

/**
 * Cria um novo meio de mobilidade elétrica e o adiciona a um vértice existente.
 * @param vertices Ponteiro para o ponteiro da lista de vértices.
 * @return  0 em caso de sucesso na criação e adição do meio 
 * @return -1 se o vértice não existe ou não pode ser vinculado
 * @return -3 se houve erro na alocação de memória para o meio.
 */
int criar_meio(NODE** vertices);

/**
 * Cria um novo meio de mobilidade elétrica e um novo vértice (se necessário) e adiciona o meio à lista de meios do vértice.
 * @param vertices Ponteiro para o ponteiro da lista de vértices.
 * @return  0 em caso de sucesso na criação do meio e vértice.
 * @return -1 se o meio não pôde ser adicionado.
 * @return -2 se houve erro ao adicionar o vértice.
 * @return -3 se houve erro na alocação de memória para o meio.
 * @return -4 se houve erro na alocação de memória para o vértice.
 */
int criar_meio_e_vertice(NODE** vertices);

/**
 * Liga dois vértices adicionando uma aresta entre eles.
 * @param vertices Ponteiro para o ponteiro da lista de vértices.
 * @return 0 em caso de sucesso na conexão dos vértices, -1 caso contrário.
 */
int ligar_vertices(NODE** vertices); 

void listar_gestores_registados(NODE* users);
void listar_clientes_registados(NODE* users);

/**
 * @brief Lista os meios de mobilidade disponíveis em ordem decrescente de autonomia.
 * @param vertices A lista de vértices do grafo.
 */
void listar_meios_disponiveis_decrescente_autonomia(NODE* meios);

/**
 * @brief Lista os meios de mobilidade em um vértice com base em um geocódigo.
 * @param vertices O ponteiro para o início da lista de vértices.
 */
void listar_meios_vertice_geocode(NODE* vertices); 

void alterar_dados_gestor(NODE** users);
void alterar_dados_cliente(NODE** users);
void alterar_dados_meios(NODE** meios);
void alterar_dados_proprio_cliente(NODE** utilizadores, USER auth);

/**
 * Lista os meios disponíveis próximos à localização fornecida.
 * @param vertices Ponteiro para a lista de vértices.
 */
void listar_meios_proximos(NODE* meios); 

void remover_cliente(NODE** utilizadores);

/**
 * @brief Remove um meio de mobilidade do vértice.
 * @param vertices O ponteiro para a lista de vértices.
 */
void remover_meio(NODE** vertices);

void alugar_meio(NODE** meios, NODE** utilizadores, USER user);

void carregar_saldo(USER auth, NODE** utilizadores);



