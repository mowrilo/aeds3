#include <stdio.h> //dijkstra
#include <stdlib.h>
#include <string.h>

#define chaveC	1
#define chaveD	2
#define chaveH	4
#define chaveS	8

int chaveNum (char c)
{
	if ((c == 'c') || (c == 'C'))	return chaveC;
	else if ((c == 'd') || (c == 'D'))	return chaveD;
	else if ((c == 'h') || (c == 'H'))	return chaveH;
	else if ((c == 's') || (c == 'S'))	return chaveS;
	else	return 0;
}

void printGrid(char*** grid, int lin, int col) 
{
	int i,j;
	for(i=(lin-1);i>=0;i--)
	{
		for(j=0;j<col;j++)
		{
			printf("%s ",grid[i][j]);
		}
		printf("\n");
	}
}

typedef struct aresta
{
	struct aresta *next;
	int vert;
} aresta;

typedef struct vertice
{
	aresta* adj;
	int chave;
	int porta;
	int buraco[3];
	int bloqueio;
}
vertice;

int indice (int i,int j, int lin)
{
	return (i*lin + j);
}

void novoVert(vertice* grafo, char* status, int indice)// . # V E 00 c C
{
	//grafo[indice] = malloc(sizeof(vertice));
	grafo[indice].chave=0;
	grafo[indice].porta=0;
	grafo[indice].buraco[0] = 0;

	if ((status[0] == 'c') || (status[0] == 'd') || (status[0] == 'h') || (status[0] == 's'))
	{
		grafo[indice].chave = chaveNum(status[0]);
	}

	else if ((status[0] == 'C') || (status[0] == 'D') || (status[0] == 'H') || (status[0] == 'S'))
	{
		grafo[indice].porta = chaveNum(status[0]);
	}
}

void adicionaAresta (vertice* vert, int destino, int indx)
{
	//aresta* a = vert->adj;
	while (vert->adj != NULL)
	{
		vert->adj = vert->adj->next;
		//if(indx == 11)	printf("de: %d\n",indx);
	}
	vert->adj = malloc(sizeof(aresta));
	vert->adj->vert = destino;
	//printf("para: %d\n", vert->adj->vert);
}

void todasArestas (vertice* vert, int nlin, int ncol, int i, int j)
{
	int icima = i+1;
	int ibaixo = i-1;
	int jdir = j+1;
	int jesq = j-1;
	if (icima < nlin)	adicionaAresta(vert, indice(icima,j,nlin),indice(i,j,nlin));//cima
	if (ibaixo >= 0)	adicionaAresta(vert, indice(ibaixo,j,nlin),indice(i,j,nlin)); //baixo
	if (jdir < ncol)	adicionaAresta(vert, indice(i,jdir,nlin),indice(i,j,nlin)); //direita
	if (jesq >= 0)	adicionaAresta(vert, indice(i,jesq,nlin),indice(i,j,nlin)); //esquerda
}

void adicionaBuraco(char* str, vertice* vert)
{
	int coord1 = str[0] - '0';
	int coord2 = str[1] - '0';

	vert->buraco[0] = 1;
	vert->buraco[1] = coord1;
	vert->buraco[2] = coord2;
}

void printVert(vertice verti)
{
	printf("%d \n%d \n%d %d %d \n", verti.chave, verti.porta, verti.buraco[0], verti.buraco[1], verti.buraco[2]);
	aresta* a = verti.adj;
	while(a != NULL)
	{
		//printf("ddrtydytd ");
		printf("%d ",a->vert);
		a = a->next;
	}
	printf("\n");
}

/*void encontraChave() //99 100 104 115
{
	or da atual com o valor de cada chave
}

int confereBloqueio() //67 68 72 83s
{
	opeacao para sobrar só o da chave de interesse
}

vertice* novoGrafo(int tam)
{
	vertice* grafo = malloc(sizeof(vertice)*)
}

int dijkstra (vertice* vert, int v, int* antecessor, int* visitado, int* dist)
{
	

}*/

int main()
{
	int lin,col,nchaves;
	int posVinicius;
	int posSaida;
	vertice* grafo;
	scanf("%d %d %d",&lin,&col,&nchaves);
	char*** grid = malloc(sizeof(char**)*lin);
	grafo = malloc(sizeof(vertice)*lin*col);
	int i;
	for (i=(lin-1);i>=0;i--)
	{
		grid[i] = malloc(sizeof(char*)*col);
		int j;
		for(j=0;j<col;j++)
		{
			grid[i][j] = malloc(2*sizeof(char));
			scanf("%s",grid[i][j]);

			if(grid[i][j][0] == 'V')
			{
				posVinicius = indice(i,j,lin);
			}

			if(grid[i][j][0] == 'E')
			{
				posSaida = indice(i,j,lin);
			}

			int ind = indice(i,j,lin);

			novoVert(grafo, grid[i][j], ind);
			if (grid[i][j][0] != '#')	todasArestas(&grafo[ind], lin, col, i, j);
			//printf("%d",grafo[ind].adj->vert);
			if (strlen(grid[i][j]) == 2)	adicionaBuraco(grid[i][j], &grafo[ind]);
		}
	}
	for (i=0;i<(lin*col);i++)
	{
		printVert(grafo[i]);
	}
	free(grafo);
//	printf("%c\n", grid[1][2][1]);
//	printGrid(grid,lin,col);
//	printf("%d %d",posVinicius,posSaida);
	return 0;
}