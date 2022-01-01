// cabe�alho com a estrutura da lista

typedef char String[100];

struct nodo
{
  struct nodo *prox;   // aponta para a pr�xima palavra da linha;
  struct nodo *abaixo; // aponta para a pr�xima linha;
  String palavra;      // armazena a palavra no nodo
  int nroLinhas;       // armazena o n�mero de linha da lista
};
