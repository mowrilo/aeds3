#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct verticeTrie
{
	struct verticeTrie *filhos[26];
	int end_of_word;
	int numTexto;
} vertice;

vertice* novoVertice (void)
{
	vertice* novo;
	novo = malloc(sizeof(vertice));
	novo->end_of_word = 0;
	novo->numTexto = 0;
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
				vert = vert->filhos[indice];
			}
			else
			{
				vertice *vert2;
				vert2 = novoVertice();
				vert->filhos[indice] = vert2;
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
			return (vert->end_of_word);
		}
	}
}

int main (int argc, char *argv[])
{
	vertice *root = novoVertice();
	inserePalavra("palavra",root);
	int a = search("palavra",root);
	printf("%d\n",a);
	return 0;
}