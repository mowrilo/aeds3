#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"trie.h"

vertice* novoVertice (void)
{
	int i;
	vertice* novo;
	novo = malloc(sizeof(vertice)); //aloca-se o espaço para um novo vertice
	novo->fimDePalavra = 0; //inicializa-se todas as variáveis
	novo->numOcorrencias = 0;
	novo->pai = NULL;
	for (i=0; i<26; i++)
	{
		novo->filhos[i] = NULL;
	}
	return novo; //retorna ponteiro para o novo vertice
}

void inserePalavra(char *palavra, vertice *root)
{
	vertice* vert = root; //é criado um ponteiro para a raiz
	int i, m = strlen(palavra);
	for (i=0; i<=m; i++) //m é o comprimento da palavra
	{
		if (i != m)
		{
			int indice = (int) palavra[i] - ((int) 'a');
			if (vert->filhos[indice] != NULL)
			{
				vert = vert->filhos[indice];//caso existe o filho apontado pelo caracter em questão, o ponteiro passa para ele
			}
			else
			{
				vertice *vert2;
				vert2 = novoVertice(); //caso nao exista o vertice para o caracter, é criado um novo
				vert2->pai = vert;//seta-se o vértice pai
				vert->filhos[indice] = vert2; //atualiza-se a lista de filhos
				vert = vert2; //passa-se o ponteiro para o novo vértice
			}
		}
		else //quando se tem um vértice para o último caracter, seta-se fimDePalavra para 1
		{
			vert->fimDePalavra = 1;
		}
	}
}

int procuraPalavra (char *palavra, vertice *root, int add)
{
	vertice* vert = root;
	int i, m = strlen(palavra);
	for (i=0; i<=m; i++) //laço semelhante à função anterior
	{
		int indice = (int) palavra[i] - ((int) 'a');
		if (i != m)
		{
			if (vert->filhos[indice] != NULL) //caso encontra o vértice do caracter, o ponteiro é passado para ele
			{
				vert = vert->filhos[indice]; 
			}
			else
			{
				return -1; //caso não encontra, retorna-se -1 indicando que a palavra não foi encontrada
			}
		}
		else
		{
			if (vert->fimDePalavra == 1) //caso encontra-se a palavra
			{
				if (add == 1) //confere-se a flag para incrementar numOcorrencias
				{
					vert->numOcorrencias++;
				}
				return vert->numOcorrencias;
			}
			else //caso a cadeia estiver presente, mas não representar uma palavra, a palavra não foi encontrada
			{
				return -1;
			}
		}
	}
}

void liberaTrie (vertice* vert) //busca em profundidade recursiva para liberar a memória da Trie
{
	int i;
	vertice* vert2;
	vert2 = NULL;
	for (i=0; i<26; i++)
	{
		if (vert->filhos[i] != NULL) //caso encontre um filho válido, a função é executada nele
		{
			vert2 = vert->filhos[i];
			liberaTrie(vert2);
		}
	}
	free(vert); //um nó só será liberado quando todos os filhos forem liberados
}