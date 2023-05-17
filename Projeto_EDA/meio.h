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

/*
 * Adiciona novo meio de mobilidade elétrica
 *  - return  0: Success
 *  - return -1: Meio already exists
 *  - return -3: Out of memory
*/
int add_meio(NODE** start, MEIO* meio);

/*
 * Encontra um meio dado um código:
 *  - Retorna o codigo
 *  - Retorna NULL if not found
*/
MEIO* find_meio_by_codigo(NODE* start, int codigo);

/*
 * Remove um meio dado um respetivo código
 *  - return  0: Success
 *  - return -1: meio not found
 *  - return -2: List is empty
*/
int remove_meio_by_codigo(NODE** start, int codigo);


/*
 * Guarda o meio em ficheiro binário.
*/
int save_meios(NODE* start);

/*
 * Guarda o meio em ficheiro texto.
*/
int save_meios_txt(NODE* start);

/*
 * Carrega os meios do ficheiro binário.
*/
int load_meios(NODE** start);
void guardar_meios(NODE* meios);

/*
 * Calcula a distância entre 2 pontos utilizando a formula de Haversine.
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