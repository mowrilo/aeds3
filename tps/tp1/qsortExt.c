#include <stdio.h>
#include <stdlib.h>

void qsortExt (FILE* file, int limMem)
{

}

int main(int* argc, char** argv[])
{
	int nMem;
	FILE* arq;
	arq = fopen("dumbo","r");
//	scanf("%d",&nMem);
	//qsortExt(arq, nMem);
	int a;
	fread(&a, sizeof(int), 1, arq);
	printf("%d\n",a);
	fclose(arq);
	return 0;
}
