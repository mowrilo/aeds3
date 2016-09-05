#include<bits/stdc++.h>

using namespace std;

int main()
{
    srand(2859285);
    ios::sync_with_stdio(false);
    int tamdicionario=100000;
    int tammaxpal=15;
    int tamtexto=50000000;
    char tmp;
    cout<<tamdicionario<<"\n";
    for(int i=0;i<tamdicionario;i++)
    {
        int tampal=rand()%tammaxpal + 1;
        for(int j=0;j<tampal;j++)
        {
            tmp='a'+rand()%26;
            cout<<tmp;
        }
        cout<<" ";
    }
    cout<<"\n"<<tamtexto<<"\n";
    for(int i=0;i<tamtexto;i++)
    {
        int tampal=rand()%tammaxpal + 1;
        for(int j=0;j<tampal;j++)
        {
            tmp='a'+rand()%26;
            cout<<tmp;
        }
        cout<<" ";
    }
    cout<<"\n";
}
