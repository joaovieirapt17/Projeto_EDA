#define _CRT_SECURE_NO_WARNINGS
#pragma once

#include "meio.h"
#define TAM 50

// Representação de um grafo orientado e pesado
typedef struct aresta {
	char geocode[TAM]; // geocodigo what3words
	float peso;
	struct aresta* proxima; //Ponteiro para a proxima aresta
}ARESTA;

typedef struct vertice {
	char geocode[TAM]; // geocodigo what3words
	NODE* arestas;
	NODE* meios; // Lista ligada com os codigos dos meios de transporte existentes neste geocodigo
	double latitude;
	double longitude;
}VERTICE;



/*
 * Adiciona um novo Vertice
 *  - return  0: Success
 *  - return -1: Vertice already exists
 *  - return -3: Out of memory
*/
int add_vertice(NODE** start, VERTICE* vertice); 

/*
 * Encontra um Vertice dado um respetivo Geocode
 *  - Retorna o Vertice
 *  - Returna NULL if not found
*/
VERTICE* find_vertice_by_geocode(NODE* start, char geocode[TAM]);

/*
 * Função para adicionar uma nova Aresta
 *  - return  0: Success
 *  - return -1: Vertice already exists
 *  - return -3: Out of memory
*/
int add_aresta(NODE** start, ARESTA* aresta); 

/*
 * Encontra uma Aresta dado um respetivo Geocode
 *  - Retorna a Aresta
 *  - Returna NULL if not found
*/
ARESTA* find_aresta_by_geocode(NODE* start, char geocode[TAM]);

float calcular_distancia_entre_vertices(VERTICE* verticeOrigem, VERTICE* verticeDestino);

/*
 * Cria uma nova Aresta
 *  - return  1: Successo
 *  - return -1: Vertices não foram encontrados
 *  - return -2: Aresta já existe
*/
int criar_aresta(NODE* grafo, char origem[], char destino[], float peso);
