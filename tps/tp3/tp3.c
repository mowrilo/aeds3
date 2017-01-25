#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
//#define NUM_THREADS 4

typedef struct parametros 
{
	/*int* vec;
	int tamanho;
	int* resultado;*/
	int** matcid;
	int n;
	int m;
	int nthreads;
	int threadid;
	int* resultados;
} parametros;

//void* maiorsoma(void* pars)
int maiorsoma(int* vec, int tamanho, int* resultado)
{
	/*parametros* par = (parametros*) pars;
	int* vec = (int*) par->vec;
	int tamanho = (int) par->tamanho;
	int* resultado = (int*) par->resultado;*/
	//printf("end dentro: %p\n", resultado);
	int* soma = malloc(sizeof(int)*tamanho);
	soma[0] = vec[0];
	int i;
	for (i=1; i<tamanho; i++)
	{
		if (vec[i] < vec[i-1])
		{
			if (soma[i-1] == soma[i-2])	soma[i] = soma[i-1]+vec[i];
			else
			{
				if (vec[i]+soma[i-2] > soma[i-1])	soma[i] = soma[i-2]+vec[i];
				else	soma[i] = soma[i-1];
			}
		}
		else
		{
			if (i > 1)	soma[i] = vec[i] + soma[i-2];
			else		soma[i] = vec[i];
		}
	}
	int maxima = soma[tamanho-1];
	free(soma);
	*resultado = maxima;
	//pthread_exit(NULL);
	//return NULL;
}

void* maiorsomaLista (void* pars) //NAO PRECISA DE VETOR DE ALOCAÇÃO. DENTRO DE UM FOR, UM IF(I%NTHREADS == THREADID)
{
	//pars -> matriz de cidades, vetor de linhas alocadas, m, vetor de resultados
	parametros* par = (parametros*) pars;
	int** matcid = (int**) par->matcid;
	int i,j;
	//int* aloc = (int*) par->vecAloc;
	int m = (int) par->m;
	int n = (int) par->n;
	int nthreads = (int) par->nthreads;
	int threadid = (int) par->threadid;
	int* resultados = (int*) par->resultados;
	
	for (i=0; i<n; i++)
	{
		if (i%nthreads == threadid)
		{
			maiorsoma(matcid[i],m,&resultados[i]);
		}
	}
	//return NULL;
}

int main(int argc, char** argv)
{
	int nthreads = atoi(argv[1]);
	int n,m;
	scanf("%d %d",&n,&m);
	int** cidade = malloc(sizeof(int*)*n);//[n][m];
	//int aloc[nthreads][n/nthreads + 1];
	int i,j;
	int valor = 0;
	struct timeval start, end;
	/*for (i=0; i<n; i++)
	{
		aloc[i%nthreads][valor] = i;
		if (i%nthreads == (nthreads-1))	valor++;
	}

	//printf("i: %d valor: %d\n", i%nthreads,valor);

	if (i%nthreads != 0)
	{
		for (j=(i%nthreads); j<nthreads; j++)	
		{
			aloc[j][valor] = -1;
			//printf("hellow\n");
		}
	}*/

	for(i=0;i<n;i++)
	{
		cidade[i] = malloc(sizeof(int)*m);
		for(j=0;j<m;j++)	scanf(" %d",&cidade[i][j]);
	}

	int* soma = malloc(sizeof(int)*n);
	pthread_t thread[nthreads];
	/*for(i=0;i<n;i++)
	{
		int rc;
		/*parametros par;
		par.vec = cidade[i];
		//for (int j=0; j<m;j++)	printf("%d ", cidade[i][j]);	
		//printf("\n");
		par.tamanho = m;
		par.resultado = &soma[i];*/
		//printf("end fora: %p\n", &soma[i]);
		//maiorsoma(&par);
		/*rc = pthread_create(&thread[i%NUM_THREADS], NULL, maiorsoma, (void*) &par);
		//printf("rc %d\n", rc);
		if (rc)
		{
			printf("ERROU\n");
			exit(-1);
		}*/
		//printf("%d\n", soma[i]);
	//}
	parametros* par = malloc(sizeof(parametros)*nthreads);
	gettimeofday(&start, NULL);
	for (i=0; i<nthreads; i++)
	{
		int rc;

		par[i].matcid = cidade;
		par[i].n = n;
		par[i].m = m;
		par[i].nthreads = nthreads;
		par[i].threadid = i;
		par[i].resultados = soma;
		rc = pthread_create(&thread[i], NULL, maiorsomaLista, (void*) &par[i]);

		if (rc)
		{
			printf("Erro ao criar thread!\n");
			exit(-1);
		}
	}


	for(i=0;i<nthreads;i++)
	{
		pthread_join(thread[i], NULL);
		//maiorsoma(cidade[i],m,&soma[i]);
	}
	free(par);

	/*for(i=0;i<n;i++)
	{
		printf("%d\n", soma[i]);	
	}*/

	int resultado;
/*	parametros par;
	par.vec = soma;
	par.tamanho = n;
	par.resultado = &resultado;*/
	maiorsoma(soma,n,&resultado);
	//pthread_create(&thread[0], NULL, maiorsoma, (void*) &par);
	//pthread_join(thread[0],NULL);
	printf("%d\n", resultado);
	gettimeofday(&end, NULL);
	int tmili;
	tmili = (int) (1000 * (end.tv_sec - start.tv_sec) +
			(end.tv_usec - start.tv_usec) / 1000);
	printf("tempo decorrido: %d ms\n", tmili);
	pthread_exit(NULL);
	return 0;
}
