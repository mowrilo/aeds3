#include <stdio.h>

#define p1d(a) printf("%d", a)
#define p2d(a,b) printf("%d %d", a, b)
#define p3d(a,b,c) printf("%d %d %d", a, b, c)


int parent(int pos)
{
	pos = pos+1;
	return (pos/2 - 1);
}

int left(int pos)
{
	pos = pos+1;
	return (2*pos - 1);
}

int right(int pos)
{
	pos = pos+1;
	return (2*pos);
}

int maior(int a, int b, int c)
{
	if (a >= b)
	{
		if (a >= c)	return a;
		else 		return c;
	}
	else
	{
		if (b >= c)	return b;
		else		return c;
	}
}

void printArray(int* array, int tam)
{
	int i;
	for (i=0; i<tam; i++)	printf("%d ",array[i]);
}

void heapify (int tam, int* array, int pos)
{
	int esq = left(pos);
	int dir = right(pos);
	int lar;
	if ((esq < tam) && (array[esq] < array[pos]))	lar = esq;
	else	lar = pos;

	if ((dir < tam) && (array[dir] < array[lar]))	lar = dir;

	if  (lar != pos)
	{
		int aux = array[pos];
		array[pos] = array[lar];
		array[lar] = aux;
		heapify(tam, array, lar);
	}
}

void buildHeap (int tam, int* array)
{
	int i;
	for (i=((tam-1)/2); i>=0; i--)		heapify(tam, array, i);
}

int retrieveMin(int* array)
{
	return array[0];
}

void tiraMin (int* tam, int* array)
{
	array[0] = array[*tam-1];
	heapify(*tam, array, 0);
	*tam = *tam - 1;
}

int main()
{
	int array[] = {16,14, 10, 8, 7, 9, 3, 2, 4, 1};
	int tam=10;
	printArray(array, tam);
	printf("\n");
	buildHeap(tam, array);
	printArray(array, tam);
	printf("\n");
	tiraMin(&tam, array);
	printArray(array, tam);
	return 0;
}