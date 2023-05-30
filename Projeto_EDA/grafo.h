/**
 * @file grafo.h
 * @brief Este arquivo contém funções relacionadas à manipulação de grafos e leitura/gravação de dados em arquivos.
 */

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

/**
 * @brief Função para encontrar o caminho mais curto entre dois vértices usando o algoritmo de Dijkstra.
 * @param vertices A lista de vértices do grafo.
 * @param geocodeInicio O código geográfico de origem.
 * @param geocodeDestino O código geográfico de destino.
 * @return Um ponteiro para o vértice de destino que representa o caminho mais curto.
 */
VERTICE* dijkstra_destino(NODE* vertices, char geocodeInicio[TAM], char geocodeFim[TAM]); 

/**
 * @brief Função para listar os meios com menos de 50% de bateria e que podem caber no caminhão.
 * @param vertices A lista de vértices do grafo.
 * @return Um ponteiro para a lista de nós contendo os meios com baixa bateria.
 */
NODE* listar_meios_menos_50(NODE* vertices); 

/**
 * @brief Função para realizar a recolha dos meios com baixa bateria a partir de um vértice de origem.
 * @param vertices A lista de vértices do grafo.
 * @param geocodeInicio O código geográfico de origem.
 */
void recolha_meios(NODE* vertices, char geocodeInicio[TAM]);

/**
 * @brief Função para salvar os vértices e seus dados em um arquivo binário.
 * @param start O nó inicial da lista de vértices.
 * @return 0 em caso de sucesso~.
 * @return -1 em caso de falha ao salvar o arquivo.
 */
int save_vertices(NODE* start);

/**
 * @brief Função para carregar os vértices e seus dados a partir de um arquivo binário.
 * @param vertices O ponteiro para a lista de vértices.
 * @return 0 em caso de sucesso
 * @return -3 em caso de falha ao abrir o arquivo.
 */
int load_vertices(NODE** vertices);

/**
 * @brief Função para salvar as arestas dos vértices em um arquivo de texto.
 * @param vertices A lista de vértices do grafo.
 */
void vertices_arestas_txt(NODE* vertices);

/**
 * @brief Função para salvar os meios dos vértices em um arquivo de texto.
 * @param vertices A lista de vértices do grafo.
 */
void vertices_meios_txt(NODE* vertices);

/**
 * @brief Função para guardar os vértices, as arestas e os meios em arquivos binários e de texto.
 * @param vertices A lista de vértices do grafo.
 */
void guardar_vertices(NODE* vertices);