#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "trie.h"
#include <malloc.h>

int main (int argc, char *argv[])
{
	struct mallinfo mi;
	int n, m, i, add;
	vertice *root = novoVertice();
	scanf("%d",&n);
	char* dicio[n];
	char* palaDicio = malloc(sizeof(char) * 15);
	//INSERÇÃO DO DICIONÁRIO
	for (i=0; i<n; i++)
	{
		dicio[i] = malloc(sizeof(char) * 15);
		scanf("%s",palaDicio);
		strcpy(dicio[i],palaDicio);
		inserePalavra(dicio[i],root);
	}

	scanf("%d",&m);

	char* palaTexto = malloc(sizeof(char) * 15);
	int search;
	//LEITURA E BUSCA DAS PALAVRAS DO TEXTO
	for (i=0; i<m; i++)
	{
		add = 1;
		scanf("%s",palaTexto);
		search = procuraPalavra(palaTexto, root, add);
	}

	//BUSCA DO DICIONÁRIO E IMPRESSÃO DAS FREQUÊNCIAS
	for (i=0; i<n; i++)
	{
		add = 0;
		search = procuraPalavra(dicio[i], root, add);
		if (i != 0)
		{
			printf(" %d",search);
		}
		else
		{
			printf("%d",search);
		}
	}

	printf("\n");
	printf("alo");
	mi = mallinfo();
	printf("%d ", mi.uordblks);

	//LIBERAÇÃO DA MEMÓRIA ALOCADA
	for (i=0; i<n; i++)
	{
		free(dicio[i]);
	}
	free(palaTexto);
	free(palaDicio);
	liberaTrie(root);
	mi = mallinfo();
	printf("%d\n", mi.uordblks);
	return 0;
}