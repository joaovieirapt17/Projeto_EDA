#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "grafo.h"
#include <limits.h>
#define INFINITO INT_MAX
#define VOLUME_MAX_CAMIAO 30

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


// Utiliza a fun��o "calcular_distancia() -> f�rmula de Haversine
float calcular_distancia_entre_vertices(VERTICE* verticeOrigem, VERTICE* verticeDestino) {
	float distancia = calcular_distancia(verticeOrigem->latitude, verticeOrigem->longitude,
		verticeDestino->latitude, verticeDestino->longitude);
	return distancia;
}

int criar_aresta(NODE* vertices, char origem[], char destino[], float peso) {

	// Encontra os v�rtices de origem e destino
	VERTICE* verticeOrigem = find_vertice_by_geocode(vertices, origem);
	VERTICE* verticeDestino = find_vertice_by_geocode(vertices, destino);

	// Se algum dos v�rtices n�o existir, retorna -1
	if (verticeOrigem == NULL || verticeDestino == NULL) {
		return -1;
	}

	// Verifica se a aresta j� existe
	ARESTA* novaAresta = find_aresta_by_geocode(verticeOrigem->arestas, destino);
	if (novaAresta != NULL) {
		return -2;
	}

	// Calcula a dist�ncia entre os v�rtices
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

	// Adiciona a nova aresta � lista de arestas do v�rtice de origem
	push(&(verticeOrigem->arestas), novaAresta, sizeof(ARESTA));

	save_vertices(vertices);

	return 1; //Sucesso
}

int remover_aresta(NODE* vertices, char origem[], char destino[]) {
	// Encontra o v�rtice de origem
	VERTICE* verticeOrigem = find_vertice_by_geocode(vertices, origem);

	// Se o v�rtice de origem n�o existir, retorna -1
	if (verticeOrigem == NULL) {
		return -1;
	}

	// Inicializa os ponteiros para as arestas atual e anterior
	NODE* arestaAtual = verticeOrigem->arestas;
	NODE* arestaAnterior = NULL;

	// Procura a aresta para remover
	while (arestaAtual != NULL) {
		ARESTA* arestaData = (ARESTA*)arestaAtual->data;

		// Verifica se esta � a aresta que queremos remover
		if (strcmp(arestaData->geocode, destino) == 0) {
			// Se a aresta estiver no in�cio da lista
			if (arestaAnterior == NULL) {
				verticeOrigem->arestas = arestaAtual->next;
			}
			// Se a aresta n�o estiver no in�cio da lista
			else {
				arestaAnterior->next = arestaAtual->next;
			}

			// Liberta a mem�ria da aresta e do n� que a cont�m
			free(arestaData);
			free(arestaAtual);

			return 1; // Sucesso
		}

		// Move para a pr�xima aresta
		arestaAnterior = arestaAtual;
		arestaAtual = arestaAtual->next;
	}

	// Se chegarmos aqui, a aresta n�o foi encontrada
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

		NODE* arestaAtual = verticeMenor->arestas;
		while (arestaAtual != NULL) {
			ARESTA* aresta = (ARESTA*)arestaAtual->data;
			VERTICE* verticeDestino = find_vertice_by_geocode(vertices, aresta->geocode);
			if (verticeDestino->visitado == 0 && verticeMenor->distancia + aresta->peso < verticeDestino->distancia) {
				verticeDestino->distancia = verticeMenor->distancia + aresta->peso;
				verticeDestino->anterior = verticeMenor;
			}
			arestaAtual = arestaAtual->next;
		}
	}
}

VERTICE* dijkstra_destino(NODE* vertices, char geocodeInicio[TAM], char geocodeFim[TAM]) {
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

	VERTICE* verticeFim = NULL;

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

		if (strcmp(verticeMenor->geocode, geocodeFim) == 0) {
			verticeFim = verticeMenor;
			break;
		}

		NODE* arestaAtual = verticeMenor->arestas;
		while (arestaAtual != NULL) {
			ARESTA* aresta = (ARESTA*)arestaAtual->data;
			VERTICE* verticeDestino = find_vertice_by_geocode(vertices, aresta->geocode);
			if (verticeDestino->visitado == 0 && verticeMenor->distancia + aresta->peso < verticeDestino->distancia) {
				verticeDestino->distancia = verticeMenor->distancia + aresta->peso;
				verticeDestino->anterior = verticeMenor;
			}
			arestaAtual = arestaAtual->next;
		}
	}

	return verticeFim;
}
NODE* listar_meios_menos_50(NODE* vertices) {
	NODE* meios_baixa_bateria_lista = NULL;
	float volumeTotal = 0;  // Vari�vel para controlar o volume total

	// Iterar sobre a lista de v�rtices
	while (vertices != NULL && volumeTotal <= VOLUME_MAX_CAMIAO) {
		VERTICE* vertice = (VERTICE*)vertices->data;
		NODE* meioAtual = vertice->meios;

		// Iterar sobre a lista de meios em cada v�rtice
		while (meioAtual != NULL && volumeTotal <= VOLUME_MAX_CAMIAO) {
			MEIO* meio = (MEIO*)meioAtual->data;

			// Se o meio tem menos de 50% de bateria e se couber no cami�o
			if (meio->bateria < 50 && volumeTotal + meio->volume <= VOLUME_MAX_CAMIAO) {
				volumeTotal += meio->volume;  // Atualiza o volume total

				// Cria um novo n� e adiciona o meio � lista de meios com baixa bateria
				NODE* novoMeio = (NODE*)malloc(sizeof(NODE));
				novoMeio->data = meio;
				novoMeio->next = meios_baixa_bateria_lista;
				meios_baixa_bateria_lista = novoMeio;

				// Interrompe a busca neste v�rtice assim que encontrar um meio com baixa bateria
				break;
			}

			meioAtual = meioAtual->next;
		}

		vertices = vertices->next;
	}

	return meios_baixa_bateria_lista;
}
void recolha_meios(NODE* vertices, char geocodeInicio[TAM]) {
	NODE* meios_baixa_bateria_lista = listar_meios_menos_50(vertices);

	if (meios_baixa_bateria_lista == NULL) {
		printf("Nenhum meio com bateria abaixo de 50%% encontrado.\n");
		return;
	}

	float volumeTotal = 0;
	NODE* meio_atual = meios_baixa_bateria_lista;

	while (meio_atual != NULL && volumeTotal <= VOLUME_MAX_CAMIAO) {
		MEIO* meio = (MEIO*)meio_atual->data;

		if (volumeTotal + meio->volume <= VOLUME_MAX_CAMIAO) {
			printf("Caminho para meio %d:\n", meio->codigo);
			dijkstra_destino(vertices, geocodeInicio, meio->geocode);
			printf("\n");

			volumeTotal += meio->volume;
		}
		else {
			printf("Cami�o cheio.\n");
			break;
		}

		meio_atual = meio_atual->next;
	}

	// Limpa a lista de meios com baixa bateria
	NODE* aux = meios_baixa_bateria_lista;
	while (aux != NULL) {
		NODE* temp = aux;
		aux = aux->next;
		free(temp);
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

		// Se falhou, ent�o exclui o arquivo.
		if (res != 0) {
			remove("vertices.dat");
			return -1;
		}

		// Guardar arestas
		a_aux = v->arestas;
		while (a_aux != NULL) {
			res = appendToFile("vertices.dat", a_aux->data, sizeof(ARESTA));

			// Se falhou, ent�o exclui o arquivo.
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

			// Se falhou, ent�o exclui o arquivo.
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
		// Aloca mem�ria para os dados
		VERTICE* vertice_data = (VERTICE*)malloc(sizeof(VERTICE));

		// L� os dados do v�rtice
		res = fread(vertice_data, sizeof(VERTICE), 1, fp);

		// Se n�o leu nada, ent�o sai do loop
		if (res == 0) break;

		// Reinicializa os ponteiros
		vertice_data->arestas = NULL;
		vertice_data->meios = NULL;

		add_vertice(vertices, vertice_data);

		for (i = 0; i < vertice_data->numeroArestas; i++) {

			// Aloca mem�ria para os dados
			ARESTA* aresta_data = (ARESTA*)malloc(sizeof(ARESTA));

			// L� os dados da aresta
			res = fread(aresta_data, sizeof(ARESTA), 1, fp);

			// Se n�o leu nada, ent�o sai do loop
			if (res == 0) break;

			add_aresta(&vertice_data->arestas, aresta_data);
		}

		for (i = 0; i < vertice_data->numeroMeios; i++) {

			// Aloca mem�ria para os dados
			MEIO* meio_data = (MEIO*)malloc(sizeof(MEIO));

			// L� os dados do meio
			res = fread(meio_data, sizeof(MEIO), 1, fp);

			// Se n�o ler nada, ent�o sai do loop 
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

		a_aux = vertice->meios;
		while (a_aux != NULL) {
			meio = (MEIO*)a_aux->data;

			fprintf(fp, "%s;%i,%lf,%lf\n", vertice->geocode, meio->codigo, meio->latitude, meio->longitude);

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

