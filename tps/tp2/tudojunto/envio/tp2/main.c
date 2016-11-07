#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include "mapa.h"
#include "heap.h"

int main()
{
	int lin,col,chavesMax,nchaves = 0,chavesAtuais = 0, nburacos = 0;
	int portas = 0;
	int buracos = 0;
	int posVinicius;
	int posSaida;
	vertice* grafo;
	scanf("%d %d %d",&lin,&col,&chavesMax); //lê os parâmetros
	char*** grid = malloc(sizeof(char**)*lin); //o grid é uma matriz de strings
	grafo = malloc(sizeof(vertice)*lin*col); //o grafo é um arranjo de vértices
	int i;
	for (i=(lin-1);i>=0;i--)
	{
		grid[i] = malloc(sizeof(char*)*col);
		int j;
		for(j=0;j<col;j++)
		{
			grid[i][j] = malloc(2*sizeof(char));
			scanf("%s",grid[i][j]);

			if(grid[i][j][0] == 'V') //guarda a posição do vinícius
			{
				posVinicius = indice(i,j,col);
			}

			if(grid[i][j][0] == 'E') //guarda a posição da saída
			{
				posSaida = indice(i,j,col);
			}

			int ind = indice(i,j,col); //calcula o índice do vértice no grafo

			novoVert(grafo, grid[i][j], ind); //cria o vertice
			if (grid[i][j][0] != '#')	todasArestas(&grafo[ind], lin, col, i, j); //cria todas as arestas de vertices adjacentes no grid
			if (strlen(grid[i][j]) == 2)	//caso o comprimento for 2, é um buraco de minhoca
			{
				adicionaBuraco(grid[i][j], &grafo[ind], col, &nburacos);
			}
		}
	}
	vertice atual = grafo[posVinicius]; //inicialização de variaveis para o Dijkstra
	int posAtual = posVinicius;
	int pesoAtual;
	int tamHeap = lin*col;
	int* distancias = malloc(sizeof(int)*lin*col);
	int** heap = malloc(sizeof(int*)*(tamHeap));
	int** auxiliaFreeHeap = malloc(sizeof(int*)*(tamHeap));

	for(i=0;i<tamHeap;i++) //inicializa heap com distancias infinitas
	{
		heap[i] = malloc(sizeof(int)*2);
		auxiliaFreeHeap[i] = heap[i]; //array que guarda os endereços usados no heap. será útil para dar free na memória,
		heap[i][0] = 100000;			//já que o heap é modificado e pode não ter mais todos os ponteiros salvos no fim
		heap[i][1] = i;
		distancias[i] = -1; //distancias incializadas como -1
	}

	heap[posVinicius][0] = 0; //a distância da posição inicial é zero
	buildHeap(tamHeap, heap); //constroi heap
	pesoAtual = 0;
	while(tamHeap > 0)
	{
		int passou=0;
		for(i=0;i<5;i++)//explora vertices do atual
		{
			if (atual.adj[i] != NULL)
			{
				int destino = atual.adj[i]->vert;
				int posHeap =  encontraHeap(heap, tamHeap, destino); //encontra no heap o vértice apontado pela aresta
				int porta = conferePorta(grafo[destino].porta, chavesAtuais); //confere se a posição é uma porta trancada
				if (porta == 1)
				{
					heap[posHeap][0] = 50000;		//caso seja, o peso é 50000 para se manter uma porta sempre acima de uma parede
					distancias[destino] = heap[posHeap][0];
				}
				if ((porta == 0) && (grafo[destino].bloqueio == 0) && (posHeap != -1))
				{
					//confere buraco, ignora arestas 0-3 se for um buraco, ignora 4 se nao for
					
					int bur = conferePorta(atual.buraco, buracos);
					if (bur == 0)
					{
						if (i < 4)
						{
							int a = pesoAtual + atual.adj[i]->peso; //eventual distancia da aresta
							
							if (a < heap[posHeap][0]) //processo de relaxamento
							{
								heap[posHeap][0] = pesoAtual + atual.adj[i]->peso;
								
								distancias[destino] = heap[posHeap][0];
								buildHeap(tamHeap,heap); //reconstroi o heap com as novas distancias
							}
						}
					}
					else
					{
						if (i == 4)
						{
							int a = pesoAtual + atual.adj[i]->peso;
							
							if (a < heap[posHeap][0])//processo de relaxamento
							{								
								heap[posHeap][0] = pesoAtual + atual.adj[i]->peso;
								passou = 1; //variável que guarda se o último vertice é um buraco de minhoca
								distancias[destino] = heap[posHeap][0];
								buildHeap(tamHeap,heap);
							}
						}
					}
				}
			}
		}

		if (passou == 0) //caso nao seja um buraco, a menor posição do heap é retirada
		{
			tiraMin(&tamHeap,heap);
		}
		else //caso seja, não é retirado do heap, só recebe peso infinito novamente, pois pode se reutilizado
		{
			heap[0][0] = 100000;
			heapify(tamHeap, heap, 0);
		}
		buracos = buracos | atual.buraco; //atualiza a bitmask de buracos
		if ((grafo[heap[0][1]].porta != 0))
		{
			if (nchaves < chavesMax)
			{
				if (conferePorta(grafo[heap[0][1]].porta, portas) == 1) //confere se passou em uma porta diferente
				{
					nchaves++;
				}
				portas = portas | grafo[heap[0][1]].porta; //atualiza a bitmask para portas
			}
			else
			{
				heap[0][0] = 50000;
				heapify(tamHeap, heap, 0);
			}
		}

		posAtual = heap[0][1];
		
		atual = grafo[posAtual];
		pesoAtual = distancias[posAtual];
		encontraChave(&nchaves, &chavesAtuais, atual.chave, chavesMax); //caso tiver uma chave no chão, o vinicius pega
	}
	printf("%d",distancias[posSaida]);

	//desalocação de memorias

	free(distancias);

	int j;
	for(i=0;i<lin;i++)
	{
		for(j=0; j<col; j++)
		{
			free(grid[i][j]);
		}
		free(grid[i]);
	}
	free(grid);

	for(i=0;i<lin*col;i++)
	{
		free(auxiliaFreeHeap[i]);
	}

	free(auxiliaFreeHeap);
	free(heap);

	for(i=0;i<(lin*col);i++)
	{
		int j;
		for(j=0;j<5;j++)
		{
			free(grafo[i].adj[j]);
		}
	}
	free(grafo);
	return 0;
}