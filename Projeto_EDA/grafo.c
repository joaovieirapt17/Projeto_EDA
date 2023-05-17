#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "grafo.h"


int add_vertice(NODE** start, VERTICE* vertice) {
	VERTICE* result = find_vertice_by_geocode(*start, vertice->geocode);
	if (result != NULL) return -1;
	return push(start, vertice, sizeof(VERTICE));
}


VERTICE* find_vertice_by_geocode(NODE* start, char geocode[TAM]) {
	NODE* aux = NULL;
	VERTICE* vertice = NULL;

	if (isEmpty(&start)) return NULL;

	aux = start;
	while (aux != NULL) {
		vertice = (VERTICE*)aux->data;

		if (strcmp(vertice->geocode, geocode) == 0) {
			return vertice;
		}

		aux = aux->next;
	}

	return NULL;
}

//--------------------------------------------------------------------

int add_aresta(NODE** start, ARESTA* aresta) {
	ARESTA* result = find_aresta_by_geocode(*start, aresta->geocode);
	if (result != NULL) return -1;
	return push(start, aresta, sizeof(ARESTA));
}


ARESTA* find_aresta_by_geocode(NODE* start, char geocode[TAM]) {
	NODE* aux = NULL;
	ARESTA* aresta = NULL;

	if (isEmpty(&start)) return NULL;

	aux = start;
	while (aux != NULL) {
		aresta = (ARESTA*)aux->data;

		if (strcmp(aresta->geocode, geocode) == 0 ) {
			return aresta;
		}

		aux = aux->next;
	}

	return NULL;
}

// Utiliza a função "calcular_distancia() -> fórmula de Haversine
float calcular_distancia_entre_vertices(VERTICE* verticeOrigem, VERTICE* verticeDestino) {
	float distancia = calcular_distancia(verticeOrigem->latitude, verticeOrigem->longitude,
		verticeDestino->latitude, verticeDestino->longitude);
	return distancia;
}

int criar_aresta(NODE* vertices, char origem[], char destino[], float peso) {
	// Encontra os vértices de origem e destino
	VERTICE* verticeOrigem = find_vertice_by_geocode(vertices, origem);
	VERTICE* verticeDestino = find_vertice_by_geocode(vertices, destino);

	// Se algum dos vértices não existir, retorna -1
	if (verticeOrigem == NULL || verticeDestino == NULL) {
		return -1;
	}

	// Verifica se a aresta já existe
	ARESTA* novaAresta = find_aresta_by_geocode(verticeOrigem->arestas, destino);
	if (novaAresta != NULL) {
		return -2;
	}

	// Calcula a distância entre os vértices
	peso = calcular_distancia_entre_vertices(verticeOrigem, verticeDestino);

	//Cria a nova aresta
	novaAresta = malloc(sizeof(ARESTA));
	if (novaAresta == NULL) {
		return -1;
	}

	// Configura os dados da nova aresta
	strcpy(novaAresta->geocode, destino);
	novaAresta->peso = peso;
	novaAresta->proxima = NULL;

	// Adiciona a nova aresta à lista de arestas do vértice de origem
	push(&(verticeOrigem->arestas), novaAresta, sizeof(ARESTA));

	return 1; //Sucesso
}