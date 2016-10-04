typedef struct livro {
	char nome[51];
	char estado;
} livro;

void stringEstante(int n, char* estante);

int buscaEstante (FILE** indice, char* nomeProcura);

int buscaLivro (FILE** estante, char* nomeProcura, int lsup, int linf);