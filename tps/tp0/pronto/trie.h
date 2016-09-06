typedef struct verticeTrie
{
	struct verticeTrie *filhos[26]; //ponteiro para os vértices filhos
	struct verticeTrie *pai; //ponteiro para o vértice pai
	int fimDePalavra; //indica se o caracter é o ultimo de uma palavra
	int numOcorrencias; //numero de ocorrencias da palavra, salvo no último vértice desta
} vertice;

vertice* novoVertice (void); //cria um novo vertice e retorna um ponteiro para ele
void inserePalavra(char *palavra, vertice *root); //insere a palavra na Trie
int procuraPalavra (char *palavra, vertice *root, int add); //procura uma palavra na Trie e retorna a frequência que ela aparece no texto, caso encontra
void liberaTrie (vertice* vert); //libera a memória alocada pela Trie