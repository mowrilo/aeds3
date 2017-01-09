#include <bits/stdc++.h>
#include <cmath>

using namespace std;

int main()
{
	int dias;
	cin >> dias;
	int i;
	for (i=1; i<=dias; i++)
	{
		int itens;
		cin >> itens;
		vector<int> peso;
		int j;//vector<int>::iterator j;

		for (j=0; j<itens; j++)
		{
			int a;
			cin >> a;
			peso.push_back(a);
		}

		sort(peso.begin(), peso.end());

		int nviagens = 0;
		int elemento = peso.size()-1;
		int debaixo = 0;

		while (debaixo < elemento)
		{
			int el = peso.at(elemento);
			int bla = ceil(50 / ((double) el)) - 1;
			if (bla <= (elemento-debaixo))
			{
				debaixo += bla;
				elemento --;
				nviagens++;
			}
			else
			{
				debaixo = elemento;
			}
		}

		cout << "Case #" << i << ": " << nviagens << endl;

	}
	return 0;
}