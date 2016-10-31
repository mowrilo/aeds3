#include <stdio.h> //dijkstra
#include <stdlib.h>

#define chavec	1
#define chaved	2
#define chaveh	4
#define chaves	8

typedef struct vertice
{
	adjancencia* adj;
	int fim;
	int chave;
	int buraco;
}
vertice;

typedef struct adjacencia
{
	struct adjacencia* next;
	int vert;
} adjacencia;

void novaAresta(vertice* grafo)
{

}

void encontraChave() //99 100 104 115
{
	or da atual com o valor de cada chave
}

int confereChave() //67 68 72 83
{
	opeacao para sobrar só o da chave de interesse
}

vertice* novoGrafo(int tam)
{
	vertice* grafo = malloc(sizeof(vertice)*)
}

int* dijkstra (vertice* grafo, int v, int comeco)
{
	int antecessor[v];
	int visitado[v];
	int dist[v];
	
}

int main()
{

	return 0;
}