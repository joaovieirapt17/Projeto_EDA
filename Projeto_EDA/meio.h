#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include <stdio.h>
#include "linkedlist.h"

typedef struct {
	int codigo; // c�digo do meio de mobilidade el�trica
	char tipo[50]; //Tipo de mobilidade el�trica
	float bateria; //Bateria	
	float autonomia; //Autonomia
	float custo; //Custo do meio 
	char geocode[100]; //Localiza��o do meio
	int status; //Status do meio de mobilidade (0 - dispon�vel, 1 - alugado)
} MEIO;

/*
 * Adiciona novo meio de mobilidade el�trica
 *  - return  0: Success
 *  - return -1: Meio already exists
 *  - return -3: Out of memory
*/
int add_meio(NODE** start, MEIO* meio);

/*
 * Encontra um meio dado um c�digo:
 *  - Retorna o codigo
 *  - Retorna NULL if not found
*/
MEIO* find_meio_by_codigo(NODE* start, int codigo);

/*
 * Remove um meio dado um respetivo c�digo
 *  - return  0: Success
 *  - return -1: meio not found
 *  - return -2: List is empty
*/
int remove_meio_by_codigo(NODE** start, int codigo);


/*
 * Guarda o meio em ficheiro bin�rio.
*/
int save_meios(NODE* start);

/*
 * Guarda o meio em ficheiro texto.
*/
int save_meios_txt(NODE* start);

/*
 * Carrega os meios do ficheiro bin�rio.
*/
int load_meios(NODE** start);
void guardar_meios(NODE* meios);
