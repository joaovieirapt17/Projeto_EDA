#define _CRT_SECURE_NO_WARNINGS

#include "linkedlist.h"

int push(NODE** start, void* data, size_t size) {
    NODE* new = NULL, * aux = NULL;
    new = (NODE*)malloc(sizeof(NODE));

    if (new == NULL) return -3;

    new->data = data;
    new->next = NULL;

    if (*start == NULL) {
        *start = new;
    }
    else {
        aux = *start;
        while (aux->next != NULL) {
            aux = aux->next;
        }
        aux->next = new;
    }

    return 0;
}

int pop(NODE** start) {
    NODE* aux = NULL, * previous = NULL;

    if (*start == NULL) {
        return -2;
    }

    aux = *start;
    if (aux->next == NULL) {
        *start = NULL;
    }
    else {
        while (aux->next != NULL) {
            previous = aux;
            aux = aux->next;
        }

        previous->next = NULL;
    }

    free(aux);
    return 0;
}

int unshift(NODE** start, void* data, size_t size) {
    NODE* new = NULL;
    new = (NODE*)malloc(sizeof(NODE));

    if (new == NULL) return -3;

    new->data = data;
    new->next = NULL;

    if (*start != NULL) {
        new->next = *start;
    }

    *start = new;
    return 0;
}

int shift(NODE** start) {
    NODE* aux = *start;

    if (aux == NULL) return -2;

    *start = aux->next;
    free(aux);
    return 0;
}

int splice(NODE** start, int index) {
    NODE* aux = NULL, * previous = NULL;
    int current_index = 0;

    if (*start == NULL) return -2;

    aux = *start;

    while (aux != NULL && current_index != index) {
        previous = aux;
        aux = aux->next;
        current_index++;
    }

    if (aux == NULL || current_index != index) return -1;

    if (previous == NULL) {
        *start = aux->next;
    }
    else {
        previous->next = aux->next;
    }

    free(aux);
    return 0;
}

int length(NODE* start) {
    NODE* aux = NULL;
    int size = 0;

    aux = start;
    while (aux != NULL) {
        size++;
        aux = aux->next;
    }

    return size;
}

void clear(NODE** start) {
    NODE* aux = NULL, * next = NULL;

    aux = *start;
    *start = NULL;
    while (aux != NULL) {
        next = aux->next;
        free(aux);
        aux = next;
    }
}

int isEmpty(NODE** start) {
    return *start == NULL;
}

NODE* last_node(NODE* start) {
    NODE* aux = start;

    if (aux == NULL) return NULL;

    while (aux->next != NULL) {
        aux = aux->next;
    }

    return aux;
}

int appendToFile(char filename[100], void* data, size_t size) {
    int res;

    FILE* fp = fopen(filename, "ab");

    if (fp == NULL) return -3;

    res = fwrite(data, size, 1, fp);
    fclose(fp);
    if (res != 1) return -1;

    return 0;
}