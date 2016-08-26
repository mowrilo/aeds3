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



int main (int argc, char *argv[])
{
	int n;
	char *padrao;
	scanf("%s",padrao);
	int m = strlen(padrao);
	int *pi = calc_pi(padrao,m);
	for (int n=0;n<m;n++)
	{
		printf("%d ",pi[n]);
	}
	printf("\n");
	free(pi);
	return 0;
}