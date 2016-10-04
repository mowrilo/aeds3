#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "biblioteca.h"

void stringEstante(int n, char* estante) //retorna a string com o nome da estante
{
	strcpy(estante, "estante");
	char* num = malloc(sizeof(char)*9);
	sprintf(num, "%d", n);
	strcat(estante, num);
	free(num);
}

int buscaEstante (FILE** indice, char* nomeProcura) //varre o arquivo indice, comparando a chave buscada com os livros presentes
{
	int estante = 0;
	rewind(*indice);
	char* procura = malloc(sizeof(char)*51);
	while (!feof(*indice))
	{
		fscanf(*indice, "%s", procura);
		if (strcmp(nomeProcura, procura) < 0)
		{
			free(procura);
			return -1;
		}
		else if (strcmp(nomeProcura, procura) == 0)
		{
			free(procura);
			return estante;
		}
		else
		{
			fscanf(*indice, "%s", procura);
			if (strcmp(nomeProcura, procura) <= 0)
			{
				free(procura);
				return estante;
			}
			else
			{
				estante++;
			}
		}
	}
	free(procura);
	return -1;
}

int buscaLivro (FILE** estante, char* nomeProcura, int lsup, int linf) //busca binária pela chave fornecida
{
	livro aux;
	while (lsup >= linf)
	{
		int med = linf + (lsup - linf)/2;
		fseek(*estante, med*sizeof(livro), SEEK_SET);
		fread(&aux, sizeof(livro), 1, *estante);
		int compara = strcmp(nomeProcura, aux.nome);
		if (compara == 0)
		{
			if (aux.estado == '0')
			{
				return (-1);
			}
			else
			{
				return med;
			}
		}
		else if (compara > 0)
		{
			linf = med+1;	
		}
		else
		{
			lsup = med-1;
		}
	}
	return (-2);
}