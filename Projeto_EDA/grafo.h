#define _CRT_SECURE_NO_WARNINGS
#pragma once

#include "meio.h"
#define TAM 50

// Representa��o de um grafo orientado e pesado
typedef struct aresta {
	char geocode[TAM]; // geoc�digo what3words
	float peso;
} *ARESTA;

typedef struct vertice {
	char geocode[TAM]; // geoc�digo what3words
	NODE* arestas;
	NODE* meios; // Lista ligada com os c�digos dos meios de transporte existentes neste geoc�digo
} *VERTICE;

