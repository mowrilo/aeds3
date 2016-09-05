#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct verticeTrie
{
	struct verticeTrie *filhos[26];
	struct verticeTrie *pai;
	int end_of_word;
	int numOcorrencias;
	int indicePai;
} vertice;

vertice* novoVertice (void)
{
	int i;
	vertice* novo;
	novo = malloc(sizeof(vertice));
	novo->end_of_word = 0;
	novo->numOcorrencias = 0;
	novo->indicePai = 100;
	novo->pai = NULL;
	for (i=0; i<26; i++)
	{
		novo->filhos[i] = NULL;
	}
	return novo;
}

void inserePalavra(char *palavra, vertice *root)
{
	vertice* vert = root;
	int i, m = strlen(palavra);
	for (i=0; i<=m; i++)
	{
		if (i != m)
		{
			int indice = (int) palavra[i] - ((int) 'a');
			if (vert->filhos[indice] != NULL)
			{
				vert = vert->filhos[indice];
			}
			else
			{
				vertice *vert2;
				vert2 = novoVertice();
				vert2->pai = vert;
				vert->filhos[indice] = vert2;
				vert2->indicePai = indice;
				vert = vert2;
			}
		}
		else
		{
			vert->end_of_word = 1;
		}
	}
}

int procuraPalavra (char *palavra, vertice *root, int add)
{
	vertice* vert = root;
	int i, m = strlen(palavra);
	for (i=0; i<=m; i++)
	{
		int indice = (int) palavra[i] - ((int) 'a');
		if (i != m)
		{
			if (vert->filhos[indice] != NULL)
			{
				vert = vert->filhos[indice];
			}
			else
			{
				return 0;
			}
		}
		else
		{
			if (add == 1)
			{
				vert->numOcorrencias++;
			}
			return vert->numOcorrencias;
		}
	}
}

void libera (vertice* vert)
{
	int i, indice;
	vertice* vert2;
	vert2 = NULL;
	for (i=0; i<26; i++)
	{
		if (vert->filhos[i] != NULL)
		{
			vert2 = vert->filhos[i];
			break;
		}
	}
	if (vert2 != NULL)
	{
		libera(vert2);
	}
	else
	{
		vert2 = vert->pai;
		indice = vert->indicePai;
		free(vert);
		if (vert2 != NULL)
		{
			vert2->filhos[indice] = NULL;
			libera(vert2);
		}
		else
		{
			return;
		}
	}
}

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
	libera(root);

	return 0;
}