#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int parent(int pos);

int left(int pos);

int right(int pos);

void heapify (int tam, int** array, int pos);

void buildHeap (int tam, int** array);

void tiraMin (int* tam, int** array);

int encontraHeap(int** heap, int tam, int pos);