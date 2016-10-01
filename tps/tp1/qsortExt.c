#include <stdio.h>
#include <stdlib.h>

int areaCheia (int* area, int n)
{
	int i, a;
	for (i=0; i < n; i++)
	{
		a = area[i];
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
	/*FILE** arquivoEscDir = arquivo;
	FILE** arquivoLeEsq = arquivo;
	FILE** arquivoEscEsq = arquivo;
	FILE** arquivoLeDir = arquivo;*/

	int *area = malloc(sizeof(int)*nMem);
	int le, ld, ee, ed, a;
	int temp;
	int count = 0;

	le = pontEsq;
	ld = pontDir;
	ee = pontEsq;
	ed = pontDir;

	//fseek(*arquivoLeEsq,pontEsq*sizeof(int),SEEK_SET);

	//fread(&temp, sizeof(int), 1, *arquivoLeEsq);
	//printf("temp0: %d\n",temp);

	//fseek(*arquivoLeDir,pontDir*sizeof(int),SEEK_SET);
	
	//fread(&temp, sizeof(int), 1, *arquivoLeEsq);
	//printf("temp1: %d\n",temp);

	//fseek(*arquivoEscEsq,pontEsq*sizeof(int),SEEK_SET);
	//fseek(*arquivoEscDir,pontDir*sizeof(int),SEEK_SET);

	if ((pontDir - pontEsq) < 1)
	{
		return;
	}
	while((ed-ee+1) > nMem)
	{
		if (ld == ed)
		{
			fseek(*arquivo,ld*sizeof(int),SEEK_SET);
			fread(&temp, sizeof(int), 1, *arquivo);
			ld--;
		}
		else if (le == ee)
		{
			fseek(*arquivo,le*sizeof(int),SEEK_SET);
			fread(&temp, sizeof(int), 1, *arquivo);
			le++;
		}
		else if ((count%2 == 0) && (count != 1))
		{
			//printf("arquivo direita. count: %d ",count);
			fseek(*arquivo,ld*sizeof(int),SEEK_SET);
			fread(&temp, sizeof(int), 1, *arquivo);
			ld--;
		}
		else
		{
			fseek(*arquivo,le*sizeof(int),SEEK_SET);
			fread(&temp, sizeof(int), 1, *arquivo);
			le++;
		}

		if (count >= nMem)
		{
			if (temp > area[nMem-1])
			{
				fseek(*arquivo,ed*sizeof(int),SEEK_SET);
				printf("escreve maior %d\n",temp);
				fwrite(&temp, sizeof(int),1,*arquivo);//escreve direita
				ed--;//move ponteiro pra esquerda
			}
			else if (temp < area[0])
			{
				fseek(*arquivo,ee*sizeof(int),SEEK_SET);
				printf("escreve menor %d\n",temp);
				fwrite(&temp, sizeof(int),1,*arquivo);//escreve direita
				//fseek(*arquivoEscEsq,1*sizeof(int),SEEK_CUR);
				ee++;/*
				escreve esquerda
				move ponteiro pra direita*/
			}
			else
			{
				if ((pontDir - ed) < (ee - pontEsq))
				{
					fseek(*arquivo,ed*sizeof(int),SEEK_SET);
					printf("chuta maior e escreve %d\n",temp);
					fwrite(&area[nMem-1], sizeof(int), 1, *arquivo);//escreve direita
					ed--;
					//escreve maior da area
					area[nMem-1] = temp;
				}
				else
				{
					fseek(*arquivo,ee*sizeof(int),SEEK_SET);
					printf("chuta menor e escreve %d\n",temp);
					fwrite(&area[0], sizeof(int), 1, *arquivo);//escreve esquerda
					ee++;
					area[0] = temp;
				}
				//escreve temp na area
				qsort(area, (nMem-1), sizeof(int), compara);;
				//reordena
			}
		}
		else
		{
			area[count] = temp;
			printf("escreve novo\n");
			qsort(area, (count+1), sizeof(int), compara); //o Compara muda de acordo com o tipo
		}

		printf("%d %d\n\n",area[0],area[1]);

		rewind(*arquivo);
		for (int i=0; i<=pontDir; i++)
		{
			fread(&a, sizeof(int), 1, *arquivo);
			printf("%d\n",a);
		}
		printf("\n\n");
		count++;
	}
	fseek(*arquivo,ee*sizeof(int),SEEK_SET);
	fwrite(&area[0], sizeof(int), 2, *arquivo);
	printf("final:\n");
	rewind(*arquivo);
	for (int i=0; i<=pontDir; i++)
	{
		fread(&a, sizeof(int), 1, *arquivo);
		printf("%d\n",a);
	}
	printf("\n\n");
	free(area);
	qsortExt(arquivo, nMem, pontDir, (ed+1));
	qsortExt(arquivo, nMem, (ee-1), pontEsq);
	//fwrite()	
}

int main(int* argc, char** argv[])
{
	int nMem = 2;
	FILE* arq;
	arq = fopen("dumbo","w+b");
//	scanf("%d",&nMem);
	//qsortExt(arq, nMem, 0, 5);
	int a, tamarq = 0;
	scanf("%d", &a);
	while (a != 0)
	{
		fwrite(&a, sizeof(int), 1, arq);
		tamarq++;
		scanf("%d",&a);
	}
	//int buf[5] = {-1,-1,-1,-1,-1};
	//buf[0] = 1;
	rewind(arq);
	qsortExt(&arq, nMem, (tamarq-1), 0);

	printf("\n\n\nfinal:\n");
	for (int i=0; i<tamarq; i++)
	{
		fread(&a, sizeof(int), 1, arq);
		printf("%d\n",a);
	}
	//int b = areaCheia(buf, 5);
//	int a;
//	fread(&a, sizeof(int), 1, arq);
	//printf("%d\n",b);
	fclose(arq);
	return 0;
}
