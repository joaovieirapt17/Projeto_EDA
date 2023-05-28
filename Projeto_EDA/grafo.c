#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "grafo.h"
#include <limits.h>
#define INFINITO INT_MAX

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

int remover_aresta(NODE* vertices, char origem[], char destino[]) {
	// Encontra o vértice de origem
	VERTICE* verticeOrigem = find_vertice_by_geocode(vertices, origem);

	// Se o vértice de origem não existir, retorna -1
	if (verticeOrigem == NULL) {
		return -1;
	}

	// Inicializa os ponteiros para as arestas atual e anterior
	NODE* arestaAtual = verticeOrigem->arestas;
	NODE* arestaAnterior = NULL;

	// Procura a aresta para remover
	while (arestaAtual != NULL) {
		ARESTA* arestaData = (ARESTA*)arestaAtual->data;

		// Verifica se esta é a aresta que queremos remover
		if (strcmp(arestaData->geocode, destino) == 0) {
			// Se a aresta estiver no início da lista
			if (arestaAnterior == NULL) {
				verticeOrigem->arestas = arestaAtual->next;
			}
			// Se a aresta não estiver no início da lista
			else {
				arestaAnterior->next = arestaAtual->next;
			}

			// Liberta a memória da aresta e do nó que a contém
			free(arestaData);
			free(arestaAtual);

			return 1; // Sucesso
		}

		// Move para a próxima aresta
		arestaAnterior = arestaAtual;
		arestaAtual = arestaAtual->next;
	}

	// Se chegarmos aqui, a aresta não foi encontrada
	return -2;
}

void dijkstra(NODE* vertices, char geocodeInicio[TAM]) {
	NODE* verticeAtual = vertices;
	VERTICE* vertice = NULL;
	while (verticeAtual != NULL) {
		vertice = (VERTICE*)verticeAtual->data;
		if (strcmp(vertice->geocode, geocodeInicio) == 0) {
			vertice->distancia = 0;
		}
		else {
			vertice->distancia = INFINITO;
		}
		vertice->visitado = 0;
		vertice->anterior = NULL;
		verticeAtual = verticeAtual->next;
	}

	while (1) {
		verticeAtual = vertices;
		VERTICE* verticeMenor = NULL;
		while (verticeAtual != NULL) {
			vertice = (VERTICE*)verticeAtual->data;
			if (vertice->visitado == 0 && (verticeMenor == NULL || vertice->distancia < verticeMenor->distancia)) {
				verticeMenor = vertice;
			}
			verticeAtual = verticeAtual->next;
		}

		if (verticeMenor == NULL) {
			break;
		}

		verticeMenor->visitado = 1;

		verticeAtual = vertices;
		while (verticeAtual != NULL) {
			vertice = (VERTICE*)verticeAtual->data;
			if (vertice->visitado == 0) {
				int distanciaEntreVertices = calcular_distancia_entre_vertices(verticeMenor, vertice);
				if (distanciaEntreVertices != -1 && verticeMenor->distancia + distanciaEntreVertices < vertice->distancia) {
					vertice->distancia = verticeMenor->distancia + distanciaEntreVertices;
					vertice->anterior = verticeMenor;
				}
			}
			verticeAtual = verticeAtual->next;
		}
	}
}


int save_vertices(NODE* start) {
	VERTICE* v = NULL;
	NODE* aux, * a_aux = NULL;
	int res;

	// Limpa o arquivo
	remove("vertices.dat");

	aux = start;
	while (aux != NULL) {
		v = (VERTICE*)aux->data;

		v->numeroArestas = length(v->arestas);
		v->numeroMeios = length(v->meios);

		// Acrescenta os dados ao arquivo
		res = appendToFile("vertices.dat", aux->data, sizeof(VERTICE));

		// Se falhou, então exclui o arquivo.
		if (res != 0) {
			remove("vertices.dat");
			return -1;
		}

		// Guardar arestas
		a_aux = v->arestas;
		while (a_aux != NULL) {
			res = appendToFile("vertices.dat", a_aux->data, sizeof(ARESTA));

			// Se falhou, então exclui o arquivo.
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

			// Se falhou, então exclui o arquivo.
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
		// Aloca memória para os dados
		VERTICE* vertice_data = (VERTICE*)malloc(sizeof(VERTICE));

		// Lê os dados do vértice
		res = fread(vertice_data, sizeof(VERTICE), 1, fp);

		// Se não leu nada, então sai do loop
		if (res == 0) break;

		// Reinicializa os ponteiros
		vertice_data->arestas = NULL;
		vertice_data->meios = NULL;

		add_vertice(vertices, vertice_data);

		for (i = 0; i < vertice_data->numeroArestas; i++) {

			// Aloca memória para os dados
			ARESTA* aresta_data = (ARESTA*)malloc(sizeof(ARESTA));

			// Lê os dados da aresta
			res = fread(aresta_data, sizeof(ARESTA), 1, fp);

			// Se não leu nada, então sai do loop
			if (res == 0) break;

			add_aresta(&vertice_data->arestas, aresta_data);
		}

		for (i = 0; i < vertice_data->numeroMeios; i++) {

			// Aloca memória para os dados
			MEIO* meio_data = (MEIO*)malloc(sizeof(MEIO));

			// Lê os dados do meio
			res = fread(meio_data, sizeof(MEIO), 1, fp);

			// Se não ler nada, então sai do loop 
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

			fprintf(fp, "%s;%s;%f\n", vertice->geocode, aresta->geocode, aresta->peso);

			a_aux = a_aux->next;
		}

		aux = aux->next;
	}

	fclose(fp); 
}

void vertices_meios_txt(NODE* vertices) {
	NODE* aux, * a_aux = NULL;
	VERTICE* vertice = NULL;
	MEIO* meio = NULL;

	FILE* fp = fopen("vertices_meios.txt", "w");

	aux = vertices;
	while (aux != NULL) {
		vertice = (VERTICE*)aux->data;

		fprintf(fp, "%s;", vertice->geocode);

		a_aux = vertice->meios;
		while (a_aux != NULL) {
			meio = (MEIO*)a_aux->data;

			fprintf(fp, "%i,%lf,%lf\n", meio->codigo, meio->latitude, meio->longitude);

			a_aux = a_aux->next;
		}

		aux = aux->next;
	}

	fclose(fp); 
}


void guardar_vertices(NODE* vertices) {
	save_vertices(vertices);
	vertices_arestas_txt(vertices);
	vertices_meios_txt(vertices);
}