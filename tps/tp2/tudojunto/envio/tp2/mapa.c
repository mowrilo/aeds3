#include <stdio.h> //dijkstra
#include <stdlib.h>
#include <string.h>
#include "mapa.h"

#define chaveC	1
#define chaveD	2
#define chaveH	4
#define chaveS	8

int chaveNum (char c) //retorna o inteiro relacionado a cada tipo de chave, para fazer a mascara de bits
{
	if ((c == 'c') || (c == 'C'))	return chaveC;
	else if ((c == 'd') || (c == 'D'))	return chaveD;
	else if ((c == 'h') || (c == 'H'))	return chaveH;
	else if ((c == 's') || (c == 'S'))	return chaveS;
	else	return 0;
}

int indice (int i,int j, int col) //dada a coordenada da posição, retorna o indice do vertice
{
	return (i*col + j);
}

void novoVert(vertice* grafo, char* status, int indice)// inicializa um novo vértice, de acordo com seu caracter no grid
{
	grafo[indice].chave=0;
	grafo[indice].porta=0;

	if ((status[0] == 'c') || (status[0] == 'd') || (status[0] == 'h') || (status[0] == 's'))
	{
		grafo[indice].chave = chaveNum(status[0]);
	}

	else if ((status[0] == 'C') || (status[0] == 'D') || (status[0] == 'H') || (status[0] == 'S'))
	{
		grafo[indice].porta = chaveNum(status[0]);
	}

	if (status[0] == '#')
	{
		grafo[indice].bloqueio = 1;
	}
}

void adicionaAresta (vertice* verti, int destino, int indx) //adiciona uma aresta no índice dado. 
{
	verti->adj[indx] = malloc(sizeof(aresta));
	verti->adj[indx]->vert = destino;
	if (indx == 4)	
	{
		verti->adj[indx]->peso = 0;
	}
	else	
	{
		verti->adj[indx]->peso = 1;	
	}
}

void todasArestas (vertice* verti, int nlin, int ncol, int i, int j)
{		//índices pré-determinados: 0-cima, 1-baixo, 2-direita, 3-esquerda, 4-buraco de minhoca
	int icima = i+1;
	int ibaixo = i-1;
	int jdir = j+1;
	int jesq = j-1;
	if (icima < nlin)
	{
		adicionaAresta(verti, indice(icima,j,ncol),0);//cima
	}
	if (ibaixo >= 0)	
	{
		adicionaAresta(verti, indice(ibaixo,j,ncol),1); //baixo
	}
	if (jdir < ncol)	
	{
		adicionaAresta(verti, indice(i,jdir,ncol),2); //direita
	}
	if (jesq >= 0)	
	{
		adicionaAresta(verti, indice(i,jesq,ncol),3); //esquerda
	}
}

void adicionaBuraco(char* str, vertice* vert, int ncol, int* nburaco)
{
	int coord1 = str[0] - '0'; //pega a posição de destino
	int coord2 = str[1] - '0';

	int i,num;
	adicionaAresta(vert, indice(coord1,coord2,ncol), 4); //cria um vertice para o destino
	num = 1;
	for(i=0;i<(*nburaco); i++) //calcula qual o número do bitmask deste buraco, de acordo com a ordem de entrada
	{
		num = num << 1;
	}
	*nburaco  = *nburaco + 1;
	vert->buraco = num;
}

void encontraChave(int* nchaves, int* chavesAtuais, int chave, int chavesMax) //adiciona uma chave no bitmask com a operação OR
{
	if (chave == 0)	return;
	*chavesAtuais = *chavesAtuais | chave;
}

int conferePorta(int porta, int chavesAtuais) //confere se chavesAtuais destranca porta
{
	//operacao and para sobrar só o da chave de interesse
	//0 destranca, 1 continua trancada
	if (porta == 0)
	{
		return 0;
	}

	if ((chavesAtuais & porta) != 0)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}