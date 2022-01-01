#include "Lista.h"

void nomeDoArquivo(String nomeArquivo, String op)
{ // fun��o que salva separa o nome do arquivo da String "op"
  int i;
  for (i = 0; i < strlen(op) && op[i + 3] != '\0'; i++)
    nomeArquivo[i] = op[i + 3];
  nomeArquivo[i] = '\0'; // acrescenta '\0' na �ltima posi��o da String
}

int verificaNumero(String numero)
{                                  // fun��o que transforma uma String em um inteiro
  int ultimo = strlen(numero) - 1; // posi��o do �ltimo caractere da String
  int multiplicador = 1;           // multiplicador representa unidade, dezena ...
  int nro = 0;                     // nro guarda o valor final do n�mero

  while (ultimo >= 0)
  { // enquanto tiver uma posi��o v�lida na String
    switch (numero[ultimo])
    { // l� todos os caracteres que represntam um n�mero da direita
      // para a esquerda
    case '0':
      nro = nro + 0 * multiplicador;
      ultimo--;
      multiplicador *= 10;
      break;
    case '1':
      nro = nro + 1 * multiplicador;
      ultimo--;
      multiplicador *= 10;
      break;
    case '2':
      nro = nro + 2 * multiplicador;
      ultimo--;
      multiplicador *= 10;
      break;
    case '3':
      nro = nro + 3 * multiplicador;
      ultimo--;
      multiplicador *= 10;
      break;
    case '4':
      nro = nro + 4 * multiplicador;
      ultimo--;
      multiplicador *= 10;
      break;
    case '5':
      nro = nro + 5 * multiplicador;
      ultimo--;
      multiplicador *= 10;
      break;
    case '6':
      nro = nro + 6 * multiplicador;
      ultimo--;
      multiplicador *= 10;
      break;
    case '7':
      nro = nro + 7 * multiplicador;
      ultimo--;
      multiplicador *= 10;
      break;
    case '8':
      nro = nro + 8 * multiplicador;
      ultimo--;
      multiplicador *= 10;
      break;
    case '9':
      nro = nro + 9 * multiplicador;
      ultimo--;
      multiplicador *= 10;
      break;
    }
  }

  return nro; // retorna o n�mero(inteiro)
}

int valoresValidos(String opcao, String numero, int *m, int *n, int nroLinhas)
{ // fun��o que verifica
  // se os valores digitados s�o validos
  int i = 3;
  int k = 0;
  if (opcao[3] == ',')
  { // verifica se foi omitida a primeira linha
    puts("Omissao de numero de linha!!!");
    return 0;
  }

  while (opcao[i] != ',' && i < strlen(opcao)) // guarda o n�mero digitado at� ser encontrado uma
                                               // v�rgula, ou o final da String seja atingida
    numero[k++] = opcao[i++];

  if (opcao[i] == '\0')
  { // caso a v�rgula tenha sido omitida
    puts("Omissao da virgula!!!");
    return 0;
  }
  else
  {
    numero[k] = '\0'; // coloca '\0' na �ltima posi��o da String n�mero
    *m = verificaNumero(numero);
  }

  k = 0;
  i++; // incrementa i para a pr�xima posi��o

  if (opcao[i] == '\0')
  { // caso o 2� n�mero tenha sido omitido
    puts("Omissao de numero de linha!!!");
    return 0;
  }
  else
  {
    while (opcao[i] != '\0') // guarda o n�mero digitado at� chegar no final da String
      numero[k++] = opcao[i++];

    numero[k] = '\0'; // coloca '\0' na �ltima posi��o da String n�mero
    *n = verificaNumero(numero);
  }

  if (*m < 0 || *n > nroLinhas)
  { // caso os valores de m ou n sejam inv�lidos
    puts("m � menor que zero ou n � maior que a ultima linha!");
    return 0;
  }

  if (*n < *m)
  { // caso n seja menor que m
    puts("n � menor que m!");
    return 0;
  }

  return 1;
}

int comandoValido(String frase)
{ // informa se os comando digitados s�o v�lidos
  if (frase[1] == 'A' || frase[1] == 'L' || frase[1] == 'U' ||
      frase[1] == 'R' || frase[1] == 'M' || frase[1] == 'S' ||
      frase[1] == 'I' || frase[1] == 'F')
    return 1;
  else
    return 0;
}
