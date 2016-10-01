#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct livro {
	char nome[51];
	char estado;
} livro;

char* stringEstante(int n)
{
	char* estante = malloc(sizeof(char)*15);
	strcpy(estante, "estante");
	char* num = malloc(sizeof(char)*7);
	sprintf(num, "%d", n);
	strcat(estante, num);
	free(num);
	return estante;
}
/*int areaCheia (int* area, int n)
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
}*/

int comparaChaves (const void *livro1, const void *livro2)
{
	livro* l1 = (livro*) livro1;
	livro* l2 = (livro*) livro2;
	return (strcmp(l1->nome, l2->nome));
}

/*int compara (const void * a, const void * b)
{
  return ( *(int*)a - *(int*)b );
}*/

void qsortExt(FILE** arquivo, int nMem, int pontEsq, int pontDir)
{
	rewind(*arquivo);
	livro *area = malloc(sizeof(livro)*nMem);
	int le, ld, ee, ed;
	livro a;
	livro temp;
	int count = 0;

	le = pontEsq;
	ld = pontDir;
	ee = pontEsq;
	ed = pontDir;
	//printf("%d %d\n", pontDir, pontEsq);
	if ((pontDir - pontEsq) < 1)
	{
		return;
	}
	while(ld >= le)
	{
		if (ld == ed)
		{
			//printf("1\n");
			fseek(*arquivo,ld*sizeof(livro),SEEK_SET);
			fread(&temp, sizeof(livro), 1, *arquivo);
			ld--;
		}
		else if (le == ee)
		{
			//printf("2\n");
			fseek(*arquivo,le*sizeof(livro),SEEK_SET);
			fread(&temp, sizeof(livro), 1, *arquivo);
			le++;
		}
		else if ((count%2 == 0) && (count != 1))
		{
			//printf("3\n");
			fseek(*arquivo,ld*sizeof(livro),SEEK_SET);
			fread(&temp, sizeof(livro), 1, *arquivo);
			ld--;
		}
		else
		{
			//printf("4\n");
			fseek(*arquivo,le*sizeof(livro),SEEK_SET);
			fread(&temp, sizeof(livro), 1, *arquivo);
			le++;
		}

		//printf("%s\n",temp.nome);
		//return;

		if (count >= nMem)
		{
			if (strcmp(temp.nome,area[nMem-1].nome) > 0)
			{
				fseek(*arquivo,ed*sizeof(livro),SEEK_SET);
				//printf("escreve maior %s\n",temp.nome);
				fwrite(&temp, sizeof(livro),1,*arquivo);//escreve direita
				ed--;//move ponteiro pra esquerda
			}
			else if (strcmp(temp.nome,area[0].nome) < 0)
			{
				fseek(*arquivo,ee*sizeof(livro),SEEK_SET);
				//printf("escreve menor %s\n",temp.nome);
				fwrite(&temp, sizeof(livro),1,*arquivo);//escreve direita
				//fseek(*arquivoEscEsq,1*sizeof(livro),SEEK_CUR);
				ee++;/*
				escreve esquerda
				move ponteiro pra direita*/
			}
			else
			{
				if ((pontDir - ed) < (ee - pontEsq))
				{
					fseek(*arquivo,ed*sizeof(livro),SEEK_SET);
					//printf("chuta maior e escreve %s\n",temp.nome);
					fwrite(&area[nMem-1], sizeof(livro), 1, *arquivo);//escreve direita
					ed--;
					//escreve maior da area
					area[nMem-1] = temp;
				}
				else
				{
					fseek(*arquivo,ee*sizeof(livro),SEEK_SET);
					//printf("chuta menor e escreve %s\n",temp.nome);
					fwrite(&area[0], sizeof(livro), 1, *arquivo);//escreve esquerda
					ee++;
					area[0] = temp;
				}
				//escreve temp na area
				qsort(area, nMem, sizeof(livro), comparaChaves);;
				//reordena
			}
		}
		else
		{
			area[count] = temp;
			//printf("escreve novo\n");
			qsort(area, (count+1), sizeof(livro), comparaChaves); //o Compara muda de acordo com o tipo
		}

		//printf("%s %s %s \n\n",area[0].nome,area[1].nome,area[2].nome);

		/*rewind(*arquivo);
		for (int i=0; i<=pontDir; i++)
		{
			fread(&a, sizeof(livro), 1, *arquivo);
			printf("%s\n",a.nome);
		}
		printf("\n\n");*/
		count++;
	}
	fseek(*arquivo,ee*sizeof(livro),SEEK_SET);
	fwrite(&area[0], sizeof(livro), nMem, *arquivo);
	//printf("final:\n");
	/*for (int i=0; i<=pontDir; i++)
	{
		fread(&a, sizeof(livro), 1, *arquivo);
		printf("%d\n",a);
	}*/
	//printf("\n\n");
	free(area);
	//printf("ponteiros direita: %d %d\n",pontDir,(ed+1));
	//printf("ponteiros esquerda: %d %d\n",(ee-1),pontEsq);
	if((pontDir - ed) > (ee - pontEsq))
	{
		qsortExt(arquivo, nMem, pontEsq, (ee-1));
		qsortExt(arquivo, nMem, (ed+1), pontDir);
	}
	else
	{
		qsortExt(arquivo, nMem, (ed+1), pontDir);
		qsortExt(arquivo, nMem, pontEsq, (ee-1));
	}
	
	//fwrite()
	rewind(*arquivo);	
}

int buscaEstante (FILE** indice, char* nomeProcura)
{
	int estante = 0;
	rewind(*indice);
	char* procura = malloc(sizeof(char)*51);
	while (!feof(*indice))
	{
		fscanf(*indice, "%s", procura);
		//printf("%s\n", procura);
		if (strcmp(nomeProcura, procura) < 0)
		{
			return -1;
		}
		else if (strcmp(nomeProcura, procura) == 0)
		{
			return estante;
		}
		else
		{
			fscanf(*indice, "%s", procura);
			//printf("%s\n", procura);
			if (strcmp(nomeProcura, procura) <= 0)
			{
				return estante;
			}
			else
			{
				estante++;
			}
		}
	}
	return -1;
}

int buscaLivro (FILE** estante, char* nomeProcura, int lsup, int linf)
{
	livro aux;
	while (lsup >= linf)
	{
		int med = linf + (lsup - linf)/2;
		fseek(*estante, med*sizeof(livro), SEEK_SET);
		fread(&aux, sizeof(livro), 1, *estante);
		//printf("%d\n", med);
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

	FILE* livrosordenados;
	FILE* indice = fopen("indice","w+");
	livrosordenados = fopen("livrosordenados","wb+");
	scanf("%d %d %d %d %d",&n,&m,&e,&l,&k);
	livro livro1;
	int pos = 0;
	for (int i=0; i<n; i++)
	{
		char aux[51];
		char aux2;
		scanf("%s %c",aux,&aux2);
		strcpy(livro1.nome,aux);
		livro1.estado = aux2;

		fwrite(&livro1, sizeof(livro), 1, livrosordenados);
		pos++;
	}
	rewind(livrosordenados);

	/*for (int i=0; i<n; i++)
	{
		fread(&livro1, sizeof(livro), 1, livrosordenados);
		printf("%s\n",livro1.nome);
	}*/
	//printf("\n\n\n");
	qsortExt(&livrosordenados, (m-1), 0, (pos-1));

	//char* estante;// = stringEstante(2);;
	
	//stringEstante(estante, 2);
	//printf("%s\n",estante);

	//rewind(livrosordenados);

	FILE** est = malloc(sizeof(FILE*)*e);

	for (int i=0; i<e; i++)
	{
		char* estante = stringEstante(i);
		//printf("%s\n",estante);
		est[i] = fopen(estante,"w+");
		//fwrite(&livro1, sizeof(livro), 1, est[i]);
	}

	//FILE* est;
	/*rewind(livrosordenados);

	for (int i=0; i<n; i++)
	{
		fread(&livro1, sizeof(livro), 1, livrosordenados);
		printf("%s\n",livro1.nome);
	}*/

	rewind(livrosordenados);

	for (int i=0; i<n; i++)
	{
		fread(&livro1, sizeof(livro), 1, livrosordenados);
		int qualEstante = (i/l);

		//printf("%s\n",estante);
		//printf("aew!\n");

		//fprintf(est[i/l],"%s","aroldo!\n");
		
		fwrite(&livro1, sizeof(livro), 1, est[i/l]);
		//printf("escrito: %s\n",livro1.nome);
		
		if (i%l==0)
		{
			if (i != 0)
			{
				fprintf(indice,"\n");
			}
			fprintf(indice,"%s ",livro1.nome);
			//fwrite(livro1.nome, sizeof(livro), 1, indice);
			//fprintf(indice," ");
		}
		else if(i%l==(l-1))
		{
			fprintf(indice,"%s",livro1.nome);
			//fwrite(livro1.nome, sizeof(livro), 1, indice);
			//fprintf(indice,"\n");
		}
	}
	//fclose(est);
	/*char* a = stringEstante(1);
	a = stringEstante(2);
	a = stringEstante(3);
	a = stringEstante(10);*/
	for (int i=0; i<e; i++)
	{
		rewind(est[i]);
	}
	char* query = malloc(sizeof(char)*51);
	for (int i=0; i<k; i++)
	{
		scanf("%s",query);
		int local = buscaEstante(&indice, query);
		
		if (local < 0)
		{
			printf("livro nao encontrado\n");
		}
		else
		{
			int estCheias = n/l;
			int nLivros;
			if (local < estCheias)
			{
				nLivros = l;
			}
			else
			{
				nLivros = n%l;
			}

			int c = buscaLivro(&est[local], query, (nLivros-1), 0);
		
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
	//fread(&livro1, sizeof(livro), 1, est);
	/*fread(&livro1, sizeof(livro), 1, est[1]);
	while(!feof(est[1]))
	{
		char *mander = livro1.nome;
		char mander1 = livro1.estado;
		printf("%s %c\n",mander, mander1);
		fread(&livro1, sizeof(livro), 1, est[1]);
	}*/
	//fclose(estR);
	//fseek(livrosordenados,k*sizeof(livro),SEEK_SET);
	//fread(&livro1, sizeof(livro), 1, livrosordenados);
	for (int i=0; i<e; i++)
	{
		fclose(est[i]);
	}
	fclose(livrosordenados);
	return 0;
}


/*
int main(int* argc, char** argv[])
{
	int nMem = 2;
	FILE* arq;
	arq = fopen("dumbo.txt","w+");
//	scanf("%d",&nMem);
	//qsortExt(arq, nMem, 0, 5);
	int a, tamarq = 0;
	scanf("%d", &a);
	while (a != 0)
	{
		fwrite(&a, sizeof(livro), 1, arq);
		tamarq++;
		scanf("%d",&a);
	}
	//int buf[5] = {-1,-1,-1,-1,-1};
	//buf[0] = 1;
	//rewind(arq);
	qsortExt(&arq, nMem, (tamarq-1), 0);
	//rewind(arq);
	printf("final:\n");
	for (int i=0; i<tamarq; i++)
	{
		fread(&a, sizeof(livro), 1, arq);
		printf("%d\n",a);
	}
	//int b = areaCheia(buf, 5);
//	int a;
//	fread(&a, sizeof(livro), 1, arq);
	//printf("%d\n",b);
	fclose(arq);
	return 0;
}
*/