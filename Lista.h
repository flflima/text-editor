#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "Nodo.h"

typedef struct nodo *Lista;

void iniciarLista(Lista *L)
{ // fun��o para iniciar a lista
  if (((*L) = (Lista)malloc(sizeof(struct nodo))) == NULL)
    exit(1);
  (*L)->abaixo = NULL;
  (*L)->prox = NULL;
  (*L)->nroLinhas = 0; // inicia o n�mero de linhas
}

int listaVazia(Lista L)
{ // verifica se a lista est� vazia
  return (L->abaixo == NULL);
}

int insereLista(Lista *L, String palavra, int k, int novaLinha)
{          // fun��o para inserir uma nova
           // linha, ou uma nova palavra, na lista
  Lista N; // nodo para uma nova linha na lista
  Lista P; // armazena uma palavra na linha

  if (listaVazia(*L))
  {
    // nenhum elemento na lista;

    if ((N = (Lista)malloc(sizeof(struct nodo))) == NULL)
    {
      puts("Erro!");
      return 0;
    }

    if ((P = (Lista)malloc(sizeof(struct nodo))) == NULL)
    {
      puts("Erro!");
      return 0;
    }

    strcpy(P->palavra, palavra);
    N->prox = P;
    P->prox = NULL;
    P->abaixo = NULL;
    N->abaixo = (*L)->abaixo;
    (*L)->abaixo = N;

    return 1;
  }

  Lista S = (*L)->abaixo; // referencia uma linha na lista

  if (k == 0 && novaLinha == 0)
  {
    // coloca uma nova palavra na linha "0" da lista, se ela
    // tiver apenas um elemento

    if ((P = (Lista)malloc(sizeof(struct nodo))) == NULL)
    {
      puts("Erro!");
      return 0;
    }

    strcpy(P->palavra, palavra);
    P->prox = NULL;
    P->abaixo = NULL;

    S = S->prox;
    while (S->prox != NULL)
      S = S->prox;

    P->prox = S->prox;
    S->prox = P;

    return 1;
  }

  if (k == 0 && (*L)->nroLinhas > 0 && novaLinha == 1)
  {
    // coloca uma nova linha na posi��o "0" se tiver mais de
    // um elemento na lista(mais de uma linha);

    if ((N = (Lista)malloc(sizeof(struct nodo))) == NULL)
    {
      puts("Erro!");
      return 0;
    }

    if ((P = (Lista)malloc(sizeof(struct nodo))) == NULL)
    {
      puts("Erro!");
      return 0;
    }

    strcpy(P->palavra, palavra);
    N->prox = P;
    P->prox = NULL;
    P->abaixo = NULL;

    N->abaixo = (*L)->abaixo;
    (*L)->abaixo = N;
    (*L)->nroLinhas++; // incrementa o n�mero de linhas

    return 1;
  }

  while (S != NULL && k > 1)
  {
    S = S->abaixo;
    k--;
  }

  if (S == NULL || k != 1)
    return 0;

  if (novaLinha == 0)
  {
    // insere uma palavra na linha k
    // se a posi��o for v�lida e tiver mais de um elemento na lista;

    if ((P = (Lista)malloc(sizeof(struct nodo))) == NULL)
    {
      puts("Erro!");
      return 0;
    }

    strcpy(P->palavra, palavra);
    P->prox = NULL;
    P->abaixo = NULL;

    S = S->abaixo->prox;
    while (S->prox != NULL)
      S = S->prox;

    P->prox = S->prox;
    S->prox = P;

    return 1;
  }
  else
  {

    if (novaLinha == 1)
    {
      // cria uma nova linha
      // se a posi��o for v�lida e tiver apenas um elemento(uma linha) na lista;

      if ((N = (Lista)malloc(sizeof(struct nodo))) == NULL)
      {
        puts("Erro!");
        return 0;
      }

      if ((P = (Lista)malloc(sizeof(struct nodo))) == NULL)
      {
        puts("Erro!");
        return 0;
      }

      strcpy(P->palavra, palavra);
      N->prox = P;
      P->prox = NULL;
      P->abaixo = NULL;

      N->abaixo = S->abaixo;
      S->abaixo = N;
      (*L)->nroLinhas++; // incrementa o n�mero de linhas

      return 1;
    }
  }
}

int removerLinhas(Lista *L, int k)
{ // fun��o para remover linha
  if (listaVazia(*L))
  {
    printf("Arquivo Vazio!!\n");
    return 0;
  }

  Lista N, P, S;
  if (k == 0) // se a linha a ser eliminada for zero
    N = (*L);
  else
    N = (*L)->abaixo;

  // se a linha k maior que zero, percorre a lista at� k ser igual a um
  while (k > 1 && N->abaixo != NULL)
  {
    N = N->abaixo;
    k--;
  }

  // caso n�o tenha encontrado a posi��o
  if (k != 1 && N->abaixo == NULL)
    return 0;

  if (k == 0)
  { // k � igual a zero
    P = N->abaixo;
    N->abaixo = P->abaixo;
    while (P != NULL)
    {
      S = P->prox;
      free(P);
      P = S;
    }
    (*L)->nroLinhas--;
    return 1;
  }

  if (k == 1)
  { // k � igual a um
    P = N->abaixo;
    N->abaixo = P->abaixo;
    while (P != NULL)
    {
      S = P->prox;
      free(P);
      P = S;
    }
    (*L)->nroLinhas--;
    return 1;
  }
  return 0;
}

int consultaLista(Lista L, int k, int linhaCorrente)
{ // fun��o que consulta um elemento no nodo
  // e imprime ele
  if (listaVazia(L))
  {
    printf("Arquivo Vazio ou o Arquivo nao foi aberto!!\n");
    return 0;
    ;
  }

  int imprime = 0; // sinaliza quando o caractere '#' deve ser
                   // impresso(a linha � a linha corrente)
  if (k == linhaCorrente)
    imprime = 1;

  Lista N = L->abaixo;

  // percorre a lista at� k ser igual a zero
  while (N->abaixo != NULL && k > 0)
  {
    N = N->abaixo;
    k--;
  }

  // caso n�o tenha encontrado a posi��o
  if (k != 0 && N->abaixo == NULL)
    return 0;

  if (k == 0)
  {
    N = N->prox;
    if (imprime == 1) // se a linha a ser impressa � a linha corrente, imprime
                      // o caractere '#'
      printf("#");
    while (N != NULL)
    {
      if (ispunct(N->palavra[strlen(N->palavra) - 1]))
      { // se o elemento for um sinal de pontua��o
        printf("\b%s ", N->palavra);
      }
      else
        printf("%s ", N->palavra);
      N = N->prox;
    }
    puts("\b");

    return 1;
  }

  return 0;
}

int imprimeIntervalo(Lista L, int linha)
{ // fun��o que imprime a lista dado um intervalo
  if (listaVazia(L))
  {
    printf("Arquivo Vazio ou o Arquivo nao foi aberto!!\n");
    return 0;
    ;
  }

  int guardaLinha = linha; // armazena a linha a ser impressa

  Lista N = L->abaixo;

  // percorre a lista at� k ser igual a zero
  while (N->abaixo != NULL && linha > 0)
  {
    N = N->abaixo;
    linha--;
  }

  // caso n�o tenha encontrado a posi��o
  if (linha != 0 && N->abaixo == NULL)
    return 0;

  if (linha == 0)
  {
    N = N->prox;
    printf("%d ", guardaLinha); // imprime o n�mero da linha
    while (N != NULL)
    {
      if (ispunct(N->palavra[strlen(N->palavra) - 1])) // se o elemento for um sinal de pontua��o
        printf("\b%s ", N->palavra);
      else
        printf("%s ", N->palavra);
      N = N->prox;
    }
    puts("\b");

    return 1;
  }

  return 0;
}

int removePalavra(Lista *L, String palavra, int k)
{ // fun��o que remove uma palavra em uma linha
  if (listaVazia(*L))
  {
    printf("Arquivo Vazio ou o Arquivo nao foi aberto!!\n");
    return 0;
    ;
  }

  int palavraEncontrada = 0; // sinaliza se a plavra desejada foi encontrada
  Lista N = (*L)->abaixo, P;

  // percorre a lista at� k ser igual a zero
  while (N->abaixo != NULL && k > 0)
  {
    N = N->abaixo;
    k--;
  }

  // caso n�o tenha encontrado a posi��o
  if (k != 0 && N->abaixo == NULL)
    return 0;

  if (k == 0)
  {
    while (N->prox != NULL)
    {
      if (strcmp(N->prox->palavra, palavra) == 0)
      { // compara se o elemento no nodo � a palavra
        // a ser removida
        P = N->prox;
        N->prox = P->prox;
        free(P);
        palavraEncontrada = 1;
      }
      else
        N = N->prox;
    }
    if (palavraEncontrada == 1)
      return 1;
  }

  return 0;
}

int substituiPalavra(Lista *L, String palavra, String substituta, int k)
{ // fun��o que substitui uma
  // palavra por outra
  if (listaVazia(*L))
  {
    printf("Arquivo Vazio ou o Arquivo nao foi aberto!!\n");
    return 0;
    ;
  }

  int palavraEncontrada = 0; // sinaliza se a plavra desejada foi encontrada
  Lista N = (*L)->abaixo;

  // percorre a lista at� k ser igual a zero
  while (N->abaixo != NULL && k > 0)
  {
    N = N->abaixo;
    k--;
  }

  // caso n�o tenha encontrado a posi��o
  if (k != 0 && N->abaixo == NULL)
    return 0;

  if (k == 0)
  {
    N = N->prox;
    while (N != NULL)
    {
      if (strcmp(N->palavra, palavra) == 0)
      {                                 // compara se o elemento no nodo � a palavra
                                        // a ser removida
        strcpy(N->palavra, substituta); // copia a palavra a substituta na palavra a ser substitu�da
        palavraEncontrada = 1;
      }
      N = N->prox;
    }
    if (palavraEncontrada == 1)
      return 1;
  }

  return 0;
}

int abreLista(Lista L, int k, FILE *arquivo, int ultimaLinha)
{ // fun��o que "abre" a lista para salvar no arquivo
  if (listaVazia(L))
  {
    printf("Arquivo Vazio!!\n");
    return 0;
  }

  int imprime = 0; // sinaliza quando '\n' deve ser impresso no arquivo(�ltima linha)
  if (k == ultimaLinha)
    imprime = 1;

  Lista N = L->abaixo;

  // percorre a lista at� k ser igual a zero
  while (N->abaixo != NULL && k > 0)
  {
    N = N->abaixo;
    k--;
  }

  // caso n�o tenha encontrado a posi��o
  if (k != 0 && N->abaixo == NULL)
    return 0;

  if (k == 0)
  {
    N = N->prox;
    while (N != NULL)
    {
      if (ispunct(N->palavra[strlen(N->palavra) - 1]))
      { // se o elemento for um sinal de pontua��o
        fprintf(arquivo, "%s", N->palavra);
      }
      else
      {
        fprintf(arquivo, "%s", N->palavra);
        if (N->prox != NULL)
          fprintf(arquivo, "%s", " ");
      }
      N = N->prox;
    }
    if (imprime != 1) // se for a �ltima linha n�o imprime o caractere '\n'
      fputs("\n", arquivo);

    return 1;
  }

  return 0;
}
