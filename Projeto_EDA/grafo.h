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
	int numeroArestas;
	int numeroMeios;
	NODE* arestas;
	NODE* meios; // Lista ligada com os codigos dos meios de transporte existentes neste geocodigo
	double latitude;
	double longitude;
	int visitado; // 0 = não visitado, 1 = visitado
	float distancia; //distancia do vertice inicial e o final
	struct vertice* anterior; // vértice anterior no caminho mais curto do vértice inicial até este vértice

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

/**
 * @brief Remove uma aresta do grafo.
 * @param vertices Array de ponteiros para vértices do grafo.
 * @param origem String que representa o código da origem da aresta a ser removida.
 * @param destino String que representa o código do destino da aresta a ser removida.
 * @return Retorna 1 em caso de sucesso na remoção da aresta. 
 * @return Retorna -1 se o vértice de origem não existir ou se a aresta não for encontrada.
 */
int remover_aresta(NODE* vertices, char origem[], char destino[]);

/**
 * @brief Implementa o algoritmo de Dijkstra para encontrar o caminho mais curto em um grafo.
 * @param vertices Um ponteiro para o primeiro nó do grafo.
 * @param geocodeInicio O código geográfico do vértice de partida.
 */
void dijkstra(NODE* vertices, char geocodeInicio[TAM]); 

VERTICE* dijkstra_destino(NODE* vertices, char geocodeInicio[TAM], char geocodeFim[TAM]); 

NODE* listar_meios_menos_50(NODE* vertices); 

void recolha_meios(NODE* vertices, char geocodeInicio[TAM]);

/**
 * @brief Funções responsáveis por guardar os vértices.
 */
int save_vertices(NODE* start);
int load_vertices(NODE** vertices);
void vertices_arestas_txt(NODE* vertices);
void vertices_meios_txt(NODE* vertices);
void guardar_vertices(NODE* vertices);