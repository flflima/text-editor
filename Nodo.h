// cabeçalho com a estrutura da lista

typedef char String[100];

struct nodo{
    struct nodo *prox;// aponta para a próxima palavra da linha;
    struct nodo *abaixo;// aponta para a próxima linha;
    String palavra;// armazena a palavra no nodo   
    int nroLinhas;// armazena o número de linha da lista
};
