#include <stdio.h> //dijkstra
#include <stdlib.h>
#include <string.h>

#define chaveC	1
#define chaveD	2
#define chaveH	4
#define chaveS	8

typedef struct aresta
{
	int peso;
	int vert;
} aresta;

typedef struct vertice
{
	aresta* adj[5];
	int chave;
	int porta;
	int buraco;
	int bloqueio;
}
vertice;

int chaveNum (char c);

int indice (int i,int j, int col);

void novoVert(vertice* grafo, char* status, int indice);

void adicionaAresta (vertice* verti, int destino, int indx);

void todasArestas (vertice* verti, int nlin, int ncol, int i, int j);

void adicionaBuraco(char* str, vertice* vert, int ncol, int* nburaco);

void encontraChave(int* nchaves, int* chavesAtuais, int chave, int chavesMax);

int conferePorta(int porta, int chavesAtuais);