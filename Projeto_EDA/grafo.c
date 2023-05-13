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


int criar_aresta(NODE* grafo, char origem[], char destino[], float peso) {
	VERTICE* verticeOrigem = find_vertice_by_geocode(grafo, origem);
	VERTICE* verticeDestino = find_vertice_by_geocode(grafo, destino);

	if (verticeOrigem == NULL || verticeDestino == NULL) {
		return -1;
	}

	ARESTA* novaAresta = find_aresta_by_geocode(verticeOrigem->arestas, destino);

	if (novaAresta != NULL) {
		return -2;
	}

	// Calcula a distância entre os vértices
	float distancia = calcular_distancia(verticeOrigem->latitude, verticeOrigem->longitude,
	verticeDestino->latitude, verticeDestino->longitude);

	peso = distancia;

	novaAresta = malloc(sizeof(ARESTA));
	if (novaAresta == NULL) {
		return -1;
	}

	strcpy(novaAresta->geocode, destino);
	novaAresta->peso = peso;
	novaAresta->proxima = NULL;

	push(&(verticeOrigem->arestas), novaAresta, sizeof(ARESTA));

	return 1;
}