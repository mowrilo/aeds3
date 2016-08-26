#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int* calc_pi(char *padrao, int m)
{
	int i,j;
	int *pi = malloc(sizeof(int)*m);
	pi[0] = 0;
	j=0;
	for (i=1;i < m;i++)
	{
		while ((j > 0) && (padrao[j] != padrao[i]))
		{
			j = pi[j-1];
		}
		if (padrao[j] == padrao[i])
		{
			j++;
		}
		pi[i] = j;
	}
	return pi;
}

void kmp(char *texto, char *padrao, int m, int n, int *pi)
{
	int i,j;
	j=0;
	for (i=0; i<n; i++)
	{
		while((j>0) && (texto[i] != padrao[j]))
		{
			j = pi[j];
		}
		if(texto[i] == padrao[j])
		{
			j++;
		}
		if(j == (m))
		{
			printf("casamento na posicao %d\n",(i-m+1));
		}
	}
}

int main (int argc, char *argv[])
{
	char *texto = "ajvnjdsnvdsvpipk";
//	char *padrao = "ababbaba";
//	int m = strlen(padrao);
	int n = strlen(texto);
//	scanf("%s",padrao);
	char *padrao;
	scanf("%s",padrao);
	int m = strlen(padrao);
	int *pi = calc_pi(padrao,m);
	/*for (int n=0;n<m;n++)
	{
		printf("%d ",pi[n]);
	}
	printf("\n");*/
	kmp(texto,padrao,m,n,pi);
	free(pi);
	return 0;
}