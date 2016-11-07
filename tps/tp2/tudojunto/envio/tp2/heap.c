#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "heap.h"

int parent(int pos) //elemento pai
{
	pos = pos+1;
	return (pos/2 - 1);
}

int left(int pos) //elemento filho da esquerda
{
	pos = pos+1;
	return (2*pos - 1);
}

int right(int pos)//elemento filho da direita
{
	pos = pos+1;
	return (2*pos);
}

void heapify (int tam, int** array, int pos) //leva um elemento para sua posição devida no heap
{
	int esq = left(pos);
	int dir = right(pos);
	int lar;
	if ((esq < tam) && (array[esq][0] < array[pos][0]))	lar = esq;
	else	lar = pos;

	if ((dir < tam) && (array[dir][0] < array[lar][0]))	lar = dir;

	if  (lar != pos)
	{
		int* aux = array[pos];
		array[pos] = array[lar];
		array[lar] = aux;
		heapify(tam, array, lar);
	}
}

void buildHeap (int tam, int** array) //constrói o heap
{
	int i;
	for (i=((tam-1)/2); i>=0; i--)		heapify(tam, array, i);
}

void tiraMin (int* tam, int** array) //tira o menor elemento e contrai o  heap
{
	array[0] = array[*tam-1];
	heapify(*tam, array, 0);
	*tam = *tam - 1;
}

int encontraHeap(int** heap, int tam, int pos) //encontra a posição de um vértice no heap
{
	int i;
	for (i=0;i<tam;i++)
	{
		if (heap[i][1] == pos)
		{
			return i;
		}
	}
	return -1;
}