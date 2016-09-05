#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"trie.h"

int main (int argc, char *argv[])
{
	int n, m, i, add;
	vertice *root = novoVertice();
	scanf("%d",&n);
	char* dicio[n];// = malloc(sizeof(char) * n);
	//**dicio = malloc(sizeof(char) * n * 15);
	char* palaDicio = malloc(sizeof(char) * 15);

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
	for (i=0; i<m; i++)
	{
		add = 1;
		scanf("%s",palaTexto);
		search = procuraPalavra(palaTexto, root, add);
		//printf("%d\n",search);
	}

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

	for (i=0; i<n; i++)
	{
		free(dicio[i]);
	}
	free(palaTexto);
	free(palaDicio);
	liberaTrie(root);

	return 0;
}