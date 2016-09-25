#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct livro {
	char nome[51];
	char estado;
} livro;

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
	livrosordenados = fopen("livrosordenados","wb+");
	scanf("%d %d %d %d %d",&n,&m,&e,&l,&k);
	livro livro1;
	//livro livroRead;
	//livroRead.nome = malloc(sizeof(char)*51);
	//char rubens;
//	printf("%d",k);
	for (int i=0; i<n; i++)
	{
		char aux[51];
		char aux2;
		scanf("%s %c",aux,&aux2);
		strcpy(livro1.nome,aux);
//	livro1.nome = "harry_potter";
		livro1.estado = aux2;

		fwrite(&livro1, sizeof(livro), 1, livrosordenados);
		/*char* nome = malloc(sizeof(char)*51);
		char estado;
		scanf("%s %c",nome,&estado);*/
		//puts("aew");
	//	scanf(" %c",&rubens);
		//printf("%c",rubens);
	//	fwrite(&rubens, sizeof(char), 1, livrosordenados);
		//fputs("\n",livrosordenados);
/*		fwrite(nome, sizeof(char)*strlen(nome), 1, livrosordenados);
		fputs(" ",livrosordenados);
		fwrite(&estado, sizeof(char), 1, livrosordenados);
		fputs("\n",livrosordenados);*/
		//fprintf(livrosordenados, "%s %c\n",nome,estado);
	}
	//char* a = malloc(sizeof(char)*51);
	//livrosordenados = fopen("livrosordenados.txt","r");
	//while(*a != EOF)
	//{
		//fread(a,(sizeof(char)*51),1,livrosordenados);
	//rewind(livrosordenados);

	fseek(livrosordenados,k*sizeof(livro),SEEK_SET);
	fread(&livro1, sizeof(livro), 1, livrosordenados);
	char *mander = livro1.nome;
	char mander1 = livro1.estado;
	printf("%s %c",mander, mander1);
	//while(fscanf(livrosordenados, "%s", a) != EOF)		printf("%s\n",a);
	//}
	//free(livroRead.nome);
	fclose(livrosordenados);
	//free(a);
	return 0;
}
