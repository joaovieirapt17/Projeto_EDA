#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <string.h>
#include "meio.h"

int add_meio(NODE** start, MEIO* meio) {
	MEIO* result = find_meio_by_codigo(*start, meio->codigo);
	if (result != NULL) return -1;
	return push(start, meio, sizeof(MEIO));
}

MEIO* find_meio_by_codigo(NODE* start, int codigo) {
	NODE* aux = NULL;
	MEIO* meio = NULL;

	if (isEmpty(&start)) return NULL;

	aux = start;
	while (aux != NULL) {
		meio = (MEIO*)aux->data;

		if (meio->codigo == codigo) {
			return meio;
		}

		aux = aux->next;
	}

	return NULL;
}

int remove_meio_by_codigo(NODE** start, int codigo) {
	NODE* aux = NULL;
	MEIO* meio = NULL;
	int index = 0;

	if (isEmpty(start)) return -2;

	aux = *start;
	while (aux != NULL) {
		meio = (MEIO*)aux->data;

		if (meio->codigo == codigo) {
			return splice(start, index);
		}

		aux = aux->next;
		index++;
	}

	return -1;
}

int save_meios(NODE* start) {
	NODE* aux = NULL;
	int res;

	remove("meios.dat"); // Remove o arquivo binário, caso já exista

	aux = start;
	while (aux != NULL) {
		res = appendToFile("meios.dat", aux->data, sizeof(MEIO));

		if (res != 0) {
			return -1;
		}

		aux = aux->next;
	}

	return 0;
}

int save_meios_txt(NODE* start) {
	NODE* aux = NULL;
	MEIO* meio = NULL;


	FILE* fp = fopen("meios.txt", "w");

	if (fp == NULL) return -3;

	aux = start;
	while (aux != NULL) {
		meio = (MEIO*)aux->data;

		fprintf(fp, "----- MEIO -----\n");
		fprintf(fp, "Codigo: %d\n", meio->codigo);
		fprintf(fp, "Tipo: %s\n", meio->tipo);
		fprintf(fp, "Bateria: %.2f\n", meio->bateria);
		fprintf(fp, "Autonomia: %.2f\n", meio->autonomia);
		fprintf(fp, "Custo: %.2f\n", meio->custo);
		fprintf(fp, "Geocode: ///%s\n", meio->geocode);
		fprintf(fp, "Status: %d\n", meio->status);

		aux = aux->next;
	}

	return 0;
}

int load_meios(NODE** start) {
	int res;

	FILE* fp = fopen("meios.dat", "rb");

	if (fp == NULL) return -3;

	do {
		MEIO* meio = (MEIO*)malloc(sizeof(MEIO));

		res = fread(meio, sizeof(MEIO), 1, fp);

		// Não leu nenhum meio, sai do loop
		if (res == 0) break;

		add_meio(start, meio);
	} while (1);

	fclose(fp);

	return 0;
}

void guardar_meios(NODE* meios) {
	save_meios(meios);
	save_meios_txt(meios);
}