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


VERTICE* find_vertice_by_geocode(NODE* start, int geocode) {
	NODE* aux = NULL;
	VERTICE* vertice = NULL;

	if (isEmpty(&start)) return NULL;

	aux = start;
	while (aux != NULL) {
		vertice = (VERTICE*)aux->data;

		if (vertice->geocode == geocode) {
			return vertice;
		}

		aux = aux->next;
	}

	return NULL;
}

