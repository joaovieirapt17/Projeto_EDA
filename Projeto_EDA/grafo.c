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

int save_vertices(NODE* start) {
	VERTICE* v = NULL;
	NODE* aux, * a_aux = NULL;
	int res;

	// Empty the file
	remove("vertices.dat");

	aux = start;
	while (aux != NULL) {
		v = (VERTICE*)aux->data;

		v->numeroArestas = length(v->arestas);
		v->numeroMeios = length(v->meios);

		// Appends data to file
		res = appendToFile("vertices.dat", aux->data, sizeof(VERTICE));

		// If failed, then delete file.
		if (res != 0) {
			remove("vertices.dat");
			return -1;
		}

		// Guardar arestas
		a_aux = v->arestas;
		while (a_aux != NULL) {
			res = appendToFile("vertices.dat", a_aux->data, sizeof(ARESTA));

			// If failed, then delete file.
			if (res != 0) {
				remove("vertices.dat");
				return -1;
			}

			a_aux = a_aux->next;
		}

		// Guardar meios
		a_aux = v->meios;
		while (a_aux != NULL) {
			res = appendToFile("vertices.dat", a_aux->data, sizeof(MEIO));

			// If failed, then delete file.
			if (res != 0) {
				remove("vertices.dat");
				return -1;
			}

			a_aux = a_aux->next;
		}


		aux = aux->next;
	}

	return 0;
}

int load_vertices(NODE** vertices) {
	int res, i;

	FILE* fp = fopen("vertices.dat", "rb");

	if (fp == NULL) return -3;

	do {
		// Allocates memory for the data
		VERTICE* vertice_data = (VERTICE*)malloc(sizeof(VERTICE));

		// Reads budget data
		res = fread(vertice_data, sizeof(VERTICE), 1, fp);

		// Didn't read anything, then break the loop
		if (res == 0) break;

		// Reset pointer
		vertice_data->arestas = NULL;
		vertice_data->meios = NULL;

		add_vertice(vertices, vertice_data);

		for (i = 0; i < vertice_data->numeroArestas; i++) {

			// Allocates memory for the data
			ARESTA* aresta_data = (ARESTA*)malloc(sizeof(ARESTA));

			// Reads details data
			res = fread(aresta_data, sizeof(ARESTA), 1, fp);

			// Didn't read anything, then break the loop
			if (res == 0) break;

			add_aresta(&vertice_data->arestas, aresta_data);
		}

		for (i = 0; i < vertice_data->numeroMeios; i++) {

			// Allocates memory for the data
			MEIO* meio_data = (MEIO*)malloc(sizeof(MEIO));

			// Reads details data
			res = fread(meio_data, sizeof(MEIO), 1, fp);

			// Didn't read anything, then break the loop
			if (res == 0) break;

			add_meio(&vertice_data->meios, meio_data);
		}
	} while (res != 0);

	fclose(fp);

	return 0;
}

void vertices_arestas_txt(NODE* vertices) {
	NODE* aux, * a_aux = NULL;
	VERTICE* vertice = NULL;
	ARESTA* aresta = NULL;

	FILE* fp = fopen("vertices_arestas.txt", "w");

	aux = vertices;
	while (aux != NULL) {
		vertice = (VERTICE*)aux->data;

		a_aux = vertice->arestas;
		while (a_aux != NULL) {
			aresta = (ARESTA*)a_aux->data;

			fprintf(fp, "%s;%s;%i\n", vertice->geocode, aresta->geocode, aresta->peso);

			a_aux = a_aux->next;
		}

		aux = aux->next;
	}
}

void vertices_meios_txt(NODE* vertices) {
	NODE* aux, * a_aux = NULL;
	VERTICE* vertice = NULL;
	MEIO* meio = NULL;

	FILE* fp = fopen("vertices_meios.txt", "w");

	aux = vertices;
	while (aux != NULL) {
		vertice = (VERTICE*)aux->data;

		fprintf(fp, "&s;", vertice->geocode);

		a_aux = vertice->meios;
		while (a_aux != NULL) {
			meio = (MEIO*)a_aux->data;

			fprintf(fp, "%i,%lf,%lf\n", meio->codigo, meio->latitude, meio->longitude);

			a_aux = a_aux->next;
		}

		aux = aux->next;
	}
}

void guardar_vertices(NODE* vertices) {
	save_vertices(vertices); 
	vertices_arestas_txt(vertices);
	vertices_meios_txt(vertices);
}