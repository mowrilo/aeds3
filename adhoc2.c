#include <stdio.h>
#include <stdlib.h>

int posNova(int lsup, int linf, int posAnt)
{
	if ((posAnt < linf) || (posAnt > lsup))		return posAnt;
	else
	{
			float a = (float) linf;
			float b = (float) lsup;
			float meio = (float) (a + ((b-a)/2));
			//int dmeio = (posAnt - (linf + (lsup-linf)/2))*(-1);*/
			return (posAnt + ((posAnt - meio)*(-1)*2));
	}
}

int main()
{
	int nGenes,reversals, nQueries;
	int vecRev[1000][2];
	int i,j;
	scanf("%d",&nGenes);
	int genome = 1;
	while (nGenes != 0)
	{	
			scanf("%d",&reversals);
	
			for (i=0; i<reversals; i++)
			{
				scanf("%d %d",&vecRev[i][0],&vecRev[i][1]);
			}
	
			scanf("%d", &nQueries);
			
			printf("Genome %d\n", genome);
			for (i=0; i<nQueries; i++)
			{
				int query;
				scanf("%d", &query);
				for (j=0; j<reversals; j++)
				{
					query = posNova(vecRev[j][1],vecRev[j][0],query);
				}
				printf("%d\n",query);
				//mander[j] = aux[j-lims];
			}
			genome ++;
			scanf("%d",&nGenes);
	}
	return 0;
}