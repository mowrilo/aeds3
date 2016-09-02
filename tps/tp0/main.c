#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct verticeTrie
{
	struct verticeTrie *filhos[26];
	int end_of_word;
} vertice;

vertice* novoVertice (void)
{
	vertice* novo;
	novo = malloc(sizeof(vertice));
	(*novo).end_of_word = 0;
	/*for (int i=0; i<26; i++)
	{
		novo->filhos[i] = NULL;
	}*/
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
				vert = vert->filhos[indice]; //consertar aqui
			}
			else
			{
				vertice *vert2;
				vert2 = novoVertice();
				vert->filhos[indice] = vert2; //consertar aqui
			}
		}
		else
		{
			vert->end_of_word = 1;
		}
	}
}

int search (char *palavra, vertice *root)
{
	
}

int main (int argc, char *argv[])
{
	vertice *root = novoVertice();
	inserePalavra("palavra",root);

	return 0;
}