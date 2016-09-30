#include <stdio.h>
#include <stdlib.h>

int areaCheia (int* area, int n)
{
	int i, a;
	for (i=0; i < n; i++)
	{
		a = area[i];
		//printf("%d ",area[i]);
		if (a >= 0)
		{
			return 0;
		}
	}
	return 1;
}

int compara (const void * a, const void * b)
{
  return ( *(int*)a - *(int*)b );
}

void qsortExt(FILE** arquivo, int nMem, int pontDir, int pontEsq)
{
	FILE** arquivoEscDir = arquivo;
	FILE** arquivoLeEsq = arquivo;
	FILE** arquivoEscEsq = arquivo;
	FILE** arquivoLeDir = arquivo;

	int *area = malloc(sizeof(int)*nMem);
	int le, ld, ee, ed;

	le = pontEsq;
	ld = pontDir;
	ee = pontEsq;
	ed = pontDir;

	fseek(arquivoLeEsq,pontEsq*sizeof(livro),SEEK_SET);
	fseek(arquivoLeDir,pontDir*sizeof(livro),SEEK_SET);

	fseek(arquivoEscEsq,pontEsq*sizeof(livro),SEEK_SET);
	fseek(arquivoEscDir,pontDir*sizeof(livro),SEEK_SET);
	
	int temp;
	int count = 0;

	while(li != ls)
	{
		if (count%2 == 0)
		{
			fread(&temp, sizeof(int), 1, arquivoLeDir);
		}
		else
		{
			fread(&temp, sizeof(int), 1, arquivoLeEsq);
		}
		if (areaCheia(area, nMem))
		{
			if (temp > area[nMem])
			{
				escreve direita
				move ponteiro pra esquerda
			}
			else if (temp < area[0])
			{
				escreve esquerda
				move ponteiro pra direita
			}
			else
			{
				escreve maior da area
				escreve temp na area
				reordena
			}
		}
		else
		{
			area[count] = temp;
			qsort(area, nMem, sizeof(int), compara);
		}
		fseek(arquivoLeDir,1*sizeof(int),SEEK_SET);
	}	
}

int main(int* argc, char** argv[])
{
	int nMem = 2;
	FILE* arq;
	arq = fopen("dumbo","w+");
//	scanf("%d",&nMem);
	//qsortExt(arq, nMem, 0, 5);
	int buf[5] = {-1,-1,-1,-1,-1};
	//buf[0] = 1;
	int b = areaCheia(buf, 5);
//	int a;
//	fread(&a, sizeof(int), 1, arq);
	printf("%d\n",b);
	fclose(arq);
	return 0;
}
