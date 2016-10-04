#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "biblioteca.h"
#include "qsortExt.h"

int comparaChaves (const void *livro1, const void *livro2) //utilizado para ordenação interna
{
	livro* l1 = (livro*) livro1;
	livro* l2 = (livro*) livro2;
	return (strcmp(l1->nome, l2->nome));
}

void qsortExt(FILE** arquivo, int nMem, livro* area, int pontEsq, int pontDir, livro* temp) //quicksort externo
{
	rewind(*arquivo);
	int le, ld, ee, ed;
	int count = 0;
	
	le = pontEsq;
	ld = pontDir;
	ee = pontEsq;
	ed = pontDir;

	if ((pontDir - pontEsq) < 1) //caso base da recursão
	{
		return;
	}
	while(ld >= le)
	{
		if (ld == ed) //não deixa os ponteiros de escrita ultrapassarem os de leitura
		{
			fseek(*arquivo,ld*sizeof(livro),SEEK_SET);
			fread(temp, sizeof(livro), 1, *arquivo);
			ld--;
		}
		else if (le == ee)
		{
			fseek(*arquivo,le*sizeof(livro),SEEK_SET);
			fread(temp, sizeof(livro), 1, *arquivo);
			le++;
		}
		else if ((count%2 == 0) && (count != 1)) //lê alternadamente
		{
			fseek(*arquivo,ld*sizeof(livro),SEEK_SET);
			fread(temp, sizeof(livro), 1, *arquivo);
			ld--;
		}
		else
		{
			fseek(*arquivo,le*sizeof(livro),SEEK_SET);
			fread(temp, sizeof(livro), 1, *arquivo);
			le++;
		}

		if (count >= nMem) //já preencheu a área
		{
			if (strcmp(temp->nome,area[nMem-1].nome) > 0)
			{
				fseek(*arquivo,ed*sizeof(livro),SEEK_SET);
				fwrite(temp, sizeof(livro),1,*arquivo);//escreve direita
				ed--;//move ponteiro pra esquerda
			}
			else if (strcmp(temp->nome,area[0].nome) < 0)
			{
				fseek(*arquivo,ee*sizeof(livro),SEEK_SET);
				fwrite(temp, sizeof(livro),1,*arquivo);
				ee++;/*
				escreve na esquerda
				move ponteiro pra direita*/
			}
			else
			{
				if ((pontDir - ed) < (ee - pontEsq)) //compara as partições antes e depois da área
				{
					fseek(*arquivo,ed*sizeof(livro),SEEK_SET);
					fwrite(&area[nMem-1], sizeof(livro), 1, *arquivo);//escreve direita
					ed--;
					//escreve maior da area
					area[nMem-1] = *temp;
				}
				else
				{
					fseek(*arquivo,ee*sizeof(livro),SEEK_SET);
					fwrite(&area[0], sizeof(livro), 1, *arquivo);//escreve esquerda
					ee++;
					area[0] = *temp;
				}
				//escreve temp na area
				qsort(area, nMem, sizeof(livro), comparaChaves);;
				//reordena
			}
		}
		else
		{ //lê para a área e a mantém ordenada
			area[count] = *temp;
			qsort(area, (count+1), sizeof(livro), comparaChaves);
		}		
		count++;
	}
	fseek(*arquivo,ee*sizeof(livro),SEEK_SET); //escreve a área, no fim da partição
	if (count > nMem) //caso a área não estiver preenchida, escreve apenas até onde se preencheu
	{
		fwrite(&area[0], sizeof(livro), nMem, *arquivo);
	}
	else
	{
		fwrite(&area[0], sizeof(livro), count, *arquivo);
	}
	memset(area, 0, (sizeof(livro)*nMem));
	if((pontDir - ed) > (ee - pontEsq)) //ordena primeiro a partição menor
	{
		qsortExt(arquivo, nMem, area, pontEsq, (ee-1), temp);
		qsortExt(arquivo, nMem, area, (ed+1), pontDir, temp);
	}
	else
	{
		qsortExt(arquivo, nMem, area, (ed+1), pontDir, temp);
		qsortExt(arquivo, nMem, area, pontEsq, (ee-1), temp);
	}

	rewind(*arquivo);	
}