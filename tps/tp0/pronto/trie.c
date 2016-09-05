#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"trie.h"

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

void liberaTrie (vertice* vert)
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
		liberaTrie(vert2);
	}
	else
	{
		vert2 = vert->pai;
		indice = vert->indicePai;
		free(vert);
		if (vert2 != NULL)
		{
			vert2->filhos[indice] = NULL;
			liberaTrie(vert2);
		}
		else
		{
			return;
		}
	}
}