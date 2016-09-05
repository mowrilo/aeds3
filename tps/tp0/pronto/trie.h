typedef struct verticeTrie
{
	struct verticeTrie *filhos[26];
	struct verticeTrie *pai;
	int end_of_word;
	int numOcorrencias;
	int indicePai;
} vertice;

vertice* novoVertice (void);
void inserePalavra(char *palavra, vertice *root);
int procuraPalavra (char *palavra, vertice *root, int add);
void liberaTrie (vertice* vert);