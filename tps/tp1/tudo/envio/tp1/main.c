#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "biblioteca.h"
#include "qsortExt.h"

int main()
{
	int n,m,e,l,k;
	/*
	n=numero de livros
	m=nmax de livros na mem principal
	e=n de estantes
	l=n de livros por estante
	k=n de pedidos
	*/

	FILE* livros_ordenados;
	FILE* indice = fopen("indice","w+");
	livros_ordenados = fopen("livros_ordenados","wb+");
	scanf("%d %d %d %d %d",&n,&m,&e,&l,&k); //lê os parâmetros
	livro livroAux; //variável auxiliar usada durante toda a execução do programa
	int i;
	char nomeAux[51]; //auxiliares para leitura dos livros a serem salvos
	char estadoAux;

	for (i=0; i<n; i++) //leitura dos livros a serem guardados em memória secundária
	{
		scanf("%s %c",nomeAux,&estadoAux);
		strcpy(livroAux.nome,nomeAux);
		livroAux.estado = estadoAux;

		fwrite(&livroAux, sizeof(livro), 1, livros_ordenados);
	}

	livro* area = malloc(sizeof(livro)*(m-1)); //aloca a memória da área de ordenação
	qsortExt(&livros_ordenados, (m-1), area, 0, (n-1), &livroAux); //ordenação
	free(area); //libera a área de ordenação

	FILE** est = malloc(sizeof(FILE*)*e); //array de ponteiros para arquivo

	char* estante = malloc(sizeof(char)*15);
	for (i=0; i<e; i++) //cria-se os arquivos que representam as estantes
	{
		stringEstante(i,estante);
		est[i] = fopen(estante,"wb+");
	}
	free(estante);

	rewind(livros_ordenados); //volta o arquivo para se acessar da primeira posição

	for (i=0; i<n; i++) //percorre o arquivo novamente para separar os livros por estante
	{
		fread(&livroAux, sizeof(livro), 1, livros_ordenados);
		int qualEstante = (i/l); //calcula em qual estante o livro deve ficar
		
		fwrite(&livroAux, sizeof(livro), 1, est[i/l]);
		
		if (i%l==0) //caso o livro 
		{
			if (i != 0)
			{
				fprintf(indice,"\n");
			}
			fprintf(indice,"%s ",livroAux.nome); //escreve os primeiros e últimos de cada estante nos índices
		}
		else if((i%l==(l-1)) || (i == (n-1)))
		{
			fprintf(indice,"%s",livroAux.nome);
		}
	}

	for (i=0; i<e; i++)
	{
		rewind(est[i]);
	}

	char* query = malloc(sizeof(char)*51);
	for (i=0; i<k; i++)
	{
		scanf("%s",query); //lê cada consulta
		int local = buscaEstante(&indice, query); //busca em qual estante está o livro, de acordo com o índice
		
		if (local < 0) //caso não encontre a estante, a pesquisa já retorna que o livro não foi encontrado
		{
			printf("livro nao encontrado\n");
		}
		else
		{
			int estCheias = n/l; //calcula o numero de estantes totalmente preenchidas
			int nLivros;
			if (local < estCheias) //calcula-se o número de livros na estante a ser vasculhada
			{
				nLivros = l;
			}
			else
			{
				nLivros = n%l;
			}

			int c = buscaLivro(&est[local], query, (nLivros-1), 0); //busca binária
		
			if (c == -1)
			{
				printf("emprestado\n");
			}
			else if (c == -2)
			{
				printf("livro nao encontrado\n");
			}
			else
			{
				printf("disponivel na posicao %d da estante %d\n", c, local);
			}
		}
	}

	for (i=0; i<e; i++)
	{
		fclose(est[i]);
	}
	fclose(livros_ordenados);
	fclose(indice);
	free(est);
	free(query);

	return 0;
}