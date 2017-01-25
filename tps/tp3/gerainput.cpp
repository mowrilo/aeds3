#include <bits/stdc++.h>

using namespace std;

#define NMAX	500

int main(int argc, char** argv)
{
	int numlin = atoi(argv[1]);
	int numcol = atoi(argv[2]);

	printf("%d %d\n", numlin, numcol);

	for (int i=0; i<numlin;i++)
	{
		for (int j=0; j<numcol; j++)
		{
			if (j == (numcol-1))	printf("%d",rand()%NMAX);
			else	printf("%d ",rand()%NMAX);
		}
		if (i != numlin-1)	printf("\n");
	}

	return 0;
}