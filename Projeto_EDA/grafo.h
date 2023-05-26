﻿#define _CRT_SECURE_NO_WARNINGS
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
	int numeroArestas;
	int numeroMeios;
	NODE* arestas;
	NODE* meios; // Lista ligada com os codigos dos meios de transporte existentes neste geocodigo
	double latitude;
	double longitude;
}VERTICE;

/**
 * @brief Adiciona um novo vértice ao grafo.
 * @param start O ponteiro para o início da lista.
 * @param vertice O ponteiro para o vértice a ser adicionado.
 * @return 0 em caso de sucesso.
 * @return -1 se o vértice já existir.
 * @return -3 se não houver memória disponível.
 */
int add_vertice(NODE** start, VERTICE* vertice); 

/**
 * @brief Encontra um vértice dado o seu geocode.
 * @param start O ponteiro para o início da lista.
 * @param geocode O geocode do vértice a ser encontrado.
 * @return O vértice encontrado.
 * @return NULL se não for encontrado.
 */
VERTICE* find_vertice_by_geocode(NODE* start, char geocode[TAM]);

/**
 * @brief Adiciona uma nova aresta ao grafo.
 * @param start O ponteiro para o início da lista.
 * @param aresta O ponteiro para a aresta a ser adicionada.
 * @return 0 em caso de sucesso.
 * @return -1 se a aresta já existir.
 * @return -3 se não houver memória disponível.
 */
int add_aresta(NODE** start, ARESTA* aresta); 

/**
 * @brief Encontra uma aresta dado o seu geocode.
 * @param start O ponteiro para o início da lista.
 * @param geocode O geocode da aresta a ser encontrada.
 * @return A aresta encontrada.
 * @return NULL se não for encontrada.
 */
ARESTA* find_aresta_by_geocode(NODE* start, char geocode[TAM]);

/**
 * @brief Calcula a distância entre dois vértices.
 * @param verticeOrigem O ponteiro para o vértice de origem.
 * @param verticeDestino O ponteiro para o vértice de destino.
 * @return A distância entre os vértices.
 */
float calcular_distancia_entre_vertices(VERTICE* verticeOrigem, VERTICE* verticeDestino);

/**
 * @brief Cria uma nova aresta no grafo.
 * @param grafo O ponteiro para o grafo.
 * @param origem O geocode do vértice de origem.
 * @param destino O geocode do vértice de destino.
 * @param peso O peso da aresta.
 * @return 1 em caso de sucesso.
 * @return -1 se os vértices não forem encontrados.
 * @return -2 se a aresta já existir.
 */
int criar_aresta(NODE* grafo, char origem[], char destino[], float peso);
