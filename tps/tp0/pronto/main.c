#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "trie.h"

int main (int argc, char *argv[])
{
	int n, m, i, add;
	vertice *root = novoVertice(); //cria-se a raiz
	scanf("%d",&n);

	char **dicio = malloc(sizeof(char*) * n); //aloca-se os N ponteiros para char
	char *palaDicio = malloc(sizeof(char) * 15); //string auxiliar para usar-se o scanf

	//INSERÇÃO DO DICIONÁRIO
	for (i=0; i<n; i++)
	{
		dicio[i] = malloc(sizeof(char) * 15); //aloca-se 15 posições para cada um dos N ponteiros
		scanf("%s",palaDicio);
		strcpy(dicio[i],palaDicio); //a palavra lida é salva no arranjo
		inserePalavra(dicio[i],root);
	}

	scanf("%d",&m);
	char* palaTexto = malloc(sizeof(char) * 15);
	int search;

	//LEITURA E BUSCA DAS PALAVRAS DO TEXTO
	add = 1;
	for (i=0; i<m; i++)
	{
		scanf("%s",palaTexto);
		search = procuraPalavra(palaTexto, root, add); //como add foi definida como 1, numOcorrencias será incrementado
	}

	//BUSCA DO DICIONÁRIO E IMPRESSÃO DAS FREQUÊNCIAS
	add = 0;
	for (i=0; i<n; i++)
	{
		search = procuraPalavra(dicio[i], root, add); //como add é 0, não se incrementa numOcorrencias
		if (i != 0) //condicional para se evitar um espaço a mais
		{
			printf(" %d",search);
		}
		else
		{
			printf("%d",search);
		}
	}
	printf("\n");

	//LIBERAÇÃO DA MEMÓRIA ALOCADA
	for (i=0; i<n; i++) //libera-se a memória de cada ponteiro
	{
		free(dicio[i]);
	}
	free(dicio); //libera-se a memória alocada para os ponteiros
	free(palaTexto); //strings auxiliares
	free(palaDicio);
	liberaTrie(root); //libera-se a Trie, começando pela raiz

	return 0;
}