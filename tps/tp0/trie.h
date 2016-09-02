#include<stdio.h>
#include<string.h>

typedef struct verticeTrie
{
	struct verticeTrie *pai;
	struct verticeTrie *filhos[26];
	int end_of_word = 0;
} vertice;

void adicionaPalavra(char *palavra);
vertice novoVertice(void);
int search(char *palavra);