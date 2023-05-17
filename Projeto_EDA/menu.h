#define _CRT_SECURE_NO_WARNINGS
#pragma once

#include "user.h"
#include <conio.h>
#include "meio.h"
#include "grafo.h"

/**
 * @brief Limpa a consola.
 */
void clear_menu();

/**
 * @brief Aguarda o utilizador pressionar qualquer tecla antes de continuar.
 */
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
 * Cria um novo meio de mobilidade el�trica e o adiciona a um v�rtice existente.
 * @param vertices Ponteiro para o ponteiro da lista de v�rtices.
 * @return  0 em caso de sucesso na cria��o e adi��o do meio 
 * @return -1 se o v�rtice n�o existe ou n�o pode ser vinculado
 * @return -3 se houve erro na aloca��o de mem�ria para o meio.
 */
int criar_meio(NODE** vertices);

/**
 * Cria um novo meio de mobilidade el�trica e um novo v�rtice (se necess�rio) e adiciona o meio � lista de meios do v�rtice.
 * @param vertices Ponteiro para o ponteiro da lista de v�rtices.
 * @return  0 em caso de sucesso na cria��o do meio e v�rtice.
 * @return -1 se o meio n�o p�de ser adicionado.
 * @return -2 se houve erro ao adicionar o v�rtice.
 * @return -3 se houve erro na aloca��o de mem�ria para o meio.
 * @return -4 se houve erro na aloca��o de mem�ria para o v�rtice.
 */
int criar_meio_e_vertice(NODE** vertices);

/**
 * Liga dois v�rtices adicionando uma aresta entre eles.
 * @param vertices Ponteiro para o ponteiro da lista de v�rtices.
 * @return 0 em caso de sucesso na conex�o dos v�rtices, -1 caso contr�rio.
 */
int ligar_vertices(NODE** vertices); 

/**
 * @brief Lista os gestores registados.
 * @param utilizadores Ponteiro para a lista de utilizadores.
 */
void listar_gestores_registados(NODE* users);

/**
 * @brief Lista os clientes registados.
 * @param utilizadores Ponteiro para a lista de utilizadores.
 */
void listar_clientes_registados(NODE* users);

/**
 * @brief Lista os meios de mobilidade dispon�veis em ordem decrescente de autonomia.
 * @param vertices A lista de v�rtices do grafo.
 */
void listar_meios_disponiveis_decrescente_autonomia(NODE* vertices);

/**
 * @brief Lista os meios de mobilidade em um v�rtice com base em um geoc�digo.
 * @param vertices O ponteiro para o in�cio da lista de v�rtices.
 */
void listar_meios_vertice_geocode(NODE* vertices); 

/**
 * @brief Altera os dados de um gestor.
 * @param utilizadores Ponteiro para a lista de utilizadores.
 */
void alterar_dados_gestor(NODE** users);

/**
 * @brief Altera os dados de um cliente.
 * @param utilizadores Ponteiro para a lista de utilizadores.
 */
void alterar_dados_cliente(NODE** users);

/**
 * @brief Altera os dados de um meio de mobilidade el�trica.
 * @param vertices Ponteiro para a lista de v�rtices.
 */
void alterar_dados_meios(NODE** vertices);

/**
 * @brief Altera os dados do pr�prio cliente.
 * @param utilizadores Ponteiro para a lista de utilizadores.
 * @param auth Utilizador autenticado.
 */
void alterar_dados_proprio_cliente(NODE** utilizadores, USER auth);

/**
 * Lista os meios dispon�veis pr�ximos � localiza��o fornecida.
 * @param vertices Ponteiro para a lista de v�rtices.
 */
void listar_meios_proximos(NODE* vertices); 

/**
 * @brief Remove um cliente da lista de utilizadores.
 * @param utilizadores Ponteiro para a lista de utilizadores.
 */
void remover_cliente(NODE** utilizadores);

/**
 * @brief Remove um meio de mobilidade do v�rtice.
 * @param vertices O ponteiro para a lista de v�rtices.
 */
void remover_meio(NODE** vertices);

/**
 * @brief Aluga um meio de mobilidade.
 * @param vertices Ponteiro para a lista de v�rtices.
 * @param utilizadores Ponteiro para a lista de utilizadores.
 * @param auth O utilizador autenticado.
 */
void alugar_meio(NODE** vertices, NODE** utilizadores, USER user);

/**
 * @brief Carrega saldo na conta do utilizador.
 * @param auth Utilizador autenticado.
 * @param utilizadores Ponteiro para a lista de utilizadores.
 */
void carregar_saldo(USER auth, NODE** utilizadores);



