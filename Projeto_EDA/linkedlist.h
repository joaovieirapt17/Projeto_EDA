#define _CRT_SECURE_NO_WARNINGS

#pragma once
#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    struct node* next;
    void* data;
}NODE;

/*
 * Adds an element to the end of the linked list
 *  - return  0: Success
 *  - return -3: Out of memory
*/
int push(NODE** start, void* data, size_t size);

/*
 * Removes the last element of the linked list
 *  - return  0: Success
 *  - return -2: Empty list
*/
int pop(NODE** start);

/*
 * Adds an element to the start of the linked list
 *  - return  0: Success
 *  - return -3: Out of memory
*/
int unshift(NODE** start, void* data, size_t size);

/*
 * Removes the first element of the linked list
 *  - return  0: Success
 *  - return -2: List is empty
*/
int shift(NODE** start);

/*
 * Removes an element given an index
 *  - return  0: Success
 *  - return -1: Element not found
 *  - return -2: List is empty
*/
int splice(NODE** start, int index);

/*
 * Returns the size of the linked list
*/
int length(NODE* start);


/*
 * Deletes all elements of the linked list
*/
void clear(NODE** start);

/*
 * Checks if the linked list is empty
 *  - return 1: is empty
 *  - return 0: not empty
*/
int isEmpty(NODE** start);

/*
 * Returns the last element of the linked list or NULL
*/
NODE* last_node(NODE* start);

/*
 * Appends data to file given the filename
 *  - return  0: Success
 *  - return -1: Unsuccessful
 *  - return -3: Error opening file
*/
int appendToFile(char filename[100], void* data, size_t size);

/*
 * Appends data to file given the filename
 *  - return  0: Success
 *  - return -1: Unsuccessful
 *  - return -3: Error opening file
*/
int appendToTextFile(char filename[100], void* data, size_t size);  //Foi criada por JV 
