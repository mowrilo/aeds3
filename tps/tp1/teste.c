#include <stdio.h>

int main()
{
	int n;
	scanf("%d",&n);
	char rubens;
	for (int i=0; i<n; i++)
	{
		scanf(" %c",&rubens);
		printf("%c",rubens);
	}
	return 0;
}
