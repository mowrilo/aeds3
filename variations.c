#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int variaLetra(char letra)
{
	int var;
	if ((letra == 'a') || (letra == 'A'))
	{
		var = 3;
	}
	else if ((letra == 'e') || (letra == 'E'))
	{
		var = 3;
	}
	else if ((letra == 'i') || (letra == 'I'))
	{
		var = 3;
	}
	else if ((letra == 'o') || (letra == 'O'))
	{
		var = 3;
	}
	else if ((letra == 's') || (letra == 'S'))
	{
		var = 3;
	}
	else
	{
		var = 2;
	}
	return var;
}

int main(int argc, char *argv[])
{
	char *password = malloc(sizeof(char) * 16); //cada senha terá no maximo 16 caracteres
	int ntestes;
	scanf("%d",&ntestes);	
	int i, j, var, m;
	for (i=0; i<ntestes; i++)
	{
		scanf("%s",password);
		m = strlen(password);
		int var = 1;
		for (j=0; j<m; j++)
		{
			var *= variaLetra(password[j]);
		}
		printf("%d\n", var);
	}
	return 0;
}