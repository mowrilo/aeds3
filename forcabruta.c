#include<stdio.h>
#include<string.h>

int main (int argc, char *argv[])
{
	char *texto = "aaaaaoo padrao s padroespadrao ascda fa kaaa";
	char *padrao = "aaa";
	int i,j,k;
	for (i = 1; i <= (strlen(texto) - strlen(padrao) + 1); i++)
	{
		k=i; j=1; 
		while((texto[k-1] == padrao[j-1]) && j <= strlen(texto))
		{
			j++;
			k++;
		}
		if (j > strlen(padrao)) {
			printf("casamento na posicao %d\n", i);
		}
	}
	return 0;
}