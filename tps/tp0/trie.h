#include<stdio.h>
#include<string.h>

typedef struct verticeTrie
{
	struct verticeTrie *pai;
	struct verticeTrie *filhos[26];
	bool end_of_word;
} vertice;

void adicionaPalavra(char *palavra);