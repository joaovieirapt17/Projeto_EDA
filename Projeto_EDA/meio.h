#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include <stdio.h>
#include "linkedlist.h"
#include "grafo.h"

typedef struct {
    int codigo;         // código do meio de mobilidade elétrica
    char tipo[50];      // Tipo de mobilidade elétrica
    float bateria;      // Bateria
    float autonomia;    // Autonomia
    float custo;        // Custo do meio 
    char geocode[100];  // Localização do meio
    int status;         // Status do meio de mobilidade (0 - disponível, 1 - alugado)
    double latitude;    // Latitude do meio
    double longitude;   // Longitude do meio
} MEIO;

/**
 * @brief Adiciona um novo meio de mobilidade elétrica a lista
 * @param start O ponteiro para o início da lista.
 * @param meio O ponteiro para o meio a ser adicionado.
 * @return  0 em caso de sucesso
 * @return -1 se o meio já existir
 * @return -3 se não houver memoria disponivel
 */
int add_meio(NODE** start, MEIO* meio);

/**
 * @brief Encontra um meio dado um código.
 * @param start O ponteiro para o início da lista.
 * @param codigo O código do meio a ser encontrado.
 * @return O ponteiro para o meio encontrado.
 * @return NULL se o meio não for encontrado.
 */
MEIO* find_meio_by_codigo(NODE* start, int codigo);

/**
 * @brief Remove um meio dado um código.
 * @param start O ponteiro para o início da lista.
 * @param codigo O código do meio a ser removido.
 * @return 0 em caso de sucesso.
 * @return -1 se o meio não for encontrado.
 * @return -2 se a lista estiver vazia.
 */
int remove_meio_by_codigo(NODE** start, int codigo);

/**
 * @brief Guarda os meios em um arquivo binário.
 * @param start O ponteiro para o início da lista.
 * @return 0 em caso de sucesso.
 * @return -1 em caso de erro ao escrever no arquivo.
 */
int save_meios(NODE* start);

/**
 * @brief Guarda os meios em um arquivo de texto.
 * @param start O ponteiro para o início da lista.
 * @return 0 em caso de sucesso.
 * @return -1 em caso de erro ao escrever no arquivo.
 */
int save_meios_txt(NODE* start);

/**
 * @brief Carrega os meios a partir de um arquivo binário.
 * @param start O ponteiro para o início da lista.
 * @return 0 em caso de sucesso.
 * @return -1 em caso de erro ao ler o arquivo.
 */
int load_meios(NODE** start);

void guardar_meios(NODE* meios);

/**
*@brief Calcula a distância entre dois pontos utilizando a fórmula de Haversine.
* @param lat1 Latitude do ponto 1.
* @param lon1 Longitude do ponto 1.
* @param lat2 Latitude do ponto 2.
* @param lon2 Longitude do ponto 2.
* @return A distância entre os pontos
*/
double calcular_distancia(double lat1, double lon1, double lat2, double lon2); 

/**
 * Carrega os vértices e seus meios de mobilidade elétrica a partir de um arquivo e os adiciona à lista de vértices.
 * @param vertices Ponteiro para o ponteiro da lista de vértices.
 * @return 0 em caso de sucesso ao carregar e adicionar os vértices,
 * @return -3 se ocorreu um erro ao abrir o arquivo,
 * @return -2 se ocorreu um erro na alocação de memória para um vértice,
 * @return -4 se ocorreu um erro na alocação de memória para um meio de mobilidade elétrica.
 */
int load_vertices(NODE** vertices) {
	int res;

	FILE* fp = fopen("vertices.dat", "rb");

	if (fp == NULL) {
		return -3;
	}

	do {
		VERTICE* vertice = (VERTICE*)malloc(sizeof(VERTICE));

		res = fread(vertice, sizeof(VERTICE), 1, fp);

		// Não leu nenhum vértice, sai do loop
		if (res == 0) {
			break;
		}

		// Carrega os meios do vértice
		do {
			MEIO* meio = (MEIO*)malloc(sizeof(MEIO));

			res = fread(meio, sizeof(MEIO), 1, fp);

			// Não leu nenhum meio, sai do loop
			if (res == 0) {
				free(meio);
				break;
			}

			add_meio(&(vertice->meios), meio);
		} while (1);

		if (vertice == NULL) {
			return -2;
		}

		add_vertice(vertices, vertice);
	} while (1);

	fclose(fp);

	return 0;
}