#include <bits/stdc++.h>
#include <cmath>

#define crad M_PI/180

using namespace std;

bool distMen(int x, int y)
{
	double dist = sqrt(pow(((double) x-50),2)+pow(((double) y-50),2));
	if (dist <= 50)	return true;
	else	return false;
}

double torad (double ang)
{
	return ang*crad;
}

int main()
{
	int ncasos;
	cin >> ncasos;
	int i;
	for (i = 1; i <= ncasos; ++i)
	{
		int p,x,y;
		cin >> p >> x >> y;
		if (distMen(x,y))
		{
			//cout << "menor" << endl;
			if (p == 0)	cout << "Case #" << i << ": white" << endl;
			else if (p == 100) cout << "Case #" << i << ": black" << endl;
			else if (p == 50)
			{
				if (x >= 50)	cout << "Case #" << i << ": black" << endl;
				else	cout << "Case #" << i << ": white" << endl;
			}
			else
			{
				if ((x == 50)  && (y >= 50))	cout << "Case #" << i << ": black" << endl;
				else
				{
					int quadranter, quadrantep;
					if (p < 50)	quadranter = 1;
					else	quadranter = 2;

					if (x > 50) quadrantep = 1;
					else 	quadrantep = 2;

					if (quadranter > quadrantep)	 cout << "Case #" << i << ": black" << endl;
					else if (quadranter < quadrantep)	cout << "Case #" << i << ": white" << endl;
					else
					{
						if (quadranter == 1)
						{
							double coefp = ((double) (y-50))/((double) (x-50));
							double coefr = tan(torad(-1* ((((double) p)/100 * 360) - 90)));

							if (coefr <= coefp)	cout << "Case #" << i << ": black" << endl;
							else	cout << "Case #" << i << ": white" << endl;
						}
						else
						{
							if (x == 50)	cout << "Case #" << i << ": black" << endl;
							else
							{
								double coefp = ((double) (y-50))/((double) (x-50));
								double coefr = tan(torad(-1* ((((double) p)/100 * 360) - 90)));

								//cout << coefr << coefp << endl;

								if (coefr <= coefp)	cout << "Case #" << i << ": black" << endl;
								else	cout << "Case #" << i << ": white" << endl;
							}
						}
					}
				}
			}
		}
		else
		{
			cout << "Case #" << i << ": white" << endl;
		}
	}
	return 0;
}