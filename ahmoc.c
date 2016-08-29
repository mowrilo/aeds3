#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int main(int argc, char *argv[])
{
	char *texto = malloc(sizeof(char) * 300000); 
	char *padrao =  malloc(sizeof(char) * 1000001);//, mult=1;
	int i,j,k,asd,count = 1;
	scanf("%s", padrao);
	while (*padrao != '0')
	{
		asd = 0;
		scanf("%s", texto);
		i=1;
		while(asd == 0)
		{
			k=i; j=1; 
			while((texto[k-1] == padrao[j-1]) && j <= strlen(texto))
			{
				j++;
				k++;
			}
			if (j > strlen(padrao)) {
				asd = 1;
			}
			i++;
			if (i == strlen(texto))
			{
				break;
			}
		}
		if (count != 1)
		{
			printf("\n");
		}
		if (asd == 1)
		{
			printf("Instancia %d\nverdadeira\n", count);
		}
		else if (asd == 0)
		{
			printf("Instancia %d\nfalsa\n", count);
		}
		count++;
		scanf("%s",padrao);
	}
	free(texto);
	free(padrao);
	return 0;
}