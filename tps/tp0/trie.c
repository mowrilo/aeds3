#include<stdio.h>
#include<string.h>
#include<stdlib.h>

vertice novoVertice (void)
{
	vertice novo = malloc(sizeof(vertice));
	return novo;
}

void adicionaPalavra(char *palavra, vertice *root)
{
	vertice vert = root;
	int i, m = strlen(palavra);
	for (i=0; i<=m; i++)
	{
		if (i != m)
		{
			indice = (int) palavra[i];
			if (vert.filhos[indice] != NULL)
			{
				vert = *(indice)
			}
			else
			{
				vert2 = novoVertice();
				vert.filhos[indice] = *vert2;
			}
		}
		else
		{
			vert.end_of_word = 1;
		}
	}
}