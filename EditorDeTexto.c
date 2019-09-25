/* *************************************************************************
   * EditorDeTexto.c                                                       *
   *           Programa em C que processa texto linha por linha.           *
   *           Alunos: Felipe Lima Freire                                  *
   *                   Leandro da Silva Mattos                             *
   *                   Paulo da Silva Santos                               *
   *                   Thiago Bezerra de Araújo                            *
   *                                                                       *
   *           Profº José Fontebasso Neto                                  *
   *           Disciplina: Estrutura de Dados II                           *
   *           Curso: Ciências da Computação                               *
   *                                                                       *
   *           Data: 01/12/2009                                            *
   *                                                                       *
   *           Obs: Para o programa fucionar no Sistema Operacional        *
   *                linux, o "system("pause");" deverá ser retirado        *
   *                do final da função "main()"                            *
   *************************************************************************   */

#include <stdlib.h>
#include "Funcoes.h"

int main(){
	Lista l; // lista
	FILE *f; // ponteiro para o arquivo
	int linhaCorrente = 0; // armazena o valor da linha atual
    int sair = 0; // variável que controla a saída do editor
    int comandoInserir = 0; // sinaliza o fim do comando inserir
    int linha = 0; // armazena o total de linhas
	int totalLinhas; // armazena o total de linhas a serem eliminadas
    int novaLinha; // sinaliza se será acrescentada uma nova linha na lista 
    int i, j, k, m, n;
	char op2; // armazena o caractere do comando desejado
	String op; // variável que armazena tanto os comandos desejados, como o nome 
               // do arquivo, como outros valores(número de linha, por exemplo)
    String nomeArquivo; // recebe o nome do arquivo
    String frase; // armazena as frases do arquivo
    String palavra; // armazena as palavras do arquivo
    String pontuacao; // armazena as pontuações do arquivo
    String numero; // armazena os números de linha
    String substituta; // armazena a palavra a ser substituída
    
	iniciarLista(&l); // inicia a lista
	
	printf("*************************** Editor de Textos **********************************\n\n");	                       
	printf("*******************************  Opcoes  **************************************\n\n");
	printf("$A nomeArquivo.extensao ---------------------------- Abrir/Criar um Arquivo\n");	
	printf("$I ------------------------- Insere novas linhas a partir da linha corrente\n");
	printf("$L m --------------------------------- Muda a linha corrente para a linha m\n");
	printf("$L -1 <enter> $I ------------------ Insere antes da primeira linha do texto\n");
	printf("$S ^x^y^ ------- Substitui a sequencia x pela sequencia y na linha corrente\n");
	printf("$S ^x^^ --------------------------- Elimina a sequencia x na linha corrente\n");
	printf("$U ---------------------------------------- Mostra o numero da ultima linha\n");
	printf("$R m,n ----------------------------- Remover linhas entre o intervalo ""m"" e ""n""\n");
	printf("$M m,n --------------------------- Mostra as linhas entre o intervalo ""m"" e ""n""\n");
	printf("$F nomeArquivo.extensao ----------------- Fechar o Editor e Salva o Arquivo\n\n");
	printf("*******************************************************************************\n\n");
	
	do{ 
        if(comandoInserir != 1){ // caso o comando inserir tenha sido sinalizado
			do{
				fgets(op,99,stdin);	// lê o comando		
			}while(op[0] != '$');
		}
			
		op[(strlen(op)-1)] = '\0'; // retira '\n' da última posição da String
		op2 = op[1]; // armazena o 2º caractere de op (comando desejado)
			
        comandoInserir = 0;
		
        switch(op2){
            case 'A':
					// Abrir um Arquivo; 
											
					nomeDoArquivo(nomeArquivo,op); // chama a função para salvar o nome do arquivo
					
                    if((f = fopen(nomeArquivo,"r")) != NULL){
						printf("\nArquivo %s aberto com sucesso!\n\n",nomeArquivo);
                                                           
						novaLinha = 1; // indica a inserção de uma nova linha 
                    
						while(fgets(frase,99,f)){ // lê uma linha, enquanto não for fim do arquivo
						
							k = 0;
							while(frase[k] != '\n' && k < strlen(frase)){ // enquanto o caractere na posição k for diferente
																		  // de '\n' e k menor que o tamanho da String	
							
								i = k;						
								
								// laço que permanece verdadeiro enquanto não for um 
								// caractere de espaço, nem um sinal de nova linha,  
								// nem um sinal de pontuação;							
								while(frase[i] != ' ' && frase[i] != '\n' && (!ispunct(frase[i])) && i < strlen(frase))	
															i++;
                                                                               
									// se o último caractere for um sinal de pontuação;
									if(ispunct(frase[i])){								
								
										pontuacao[0] = frase[i];
										pontuacao[1] = '\0';
										
										i -= k; // total de elementos da String palavra
										
										for(j = 0; j < i; j++)
										      palavra[j] = frase[k++];
											
											palavra[j] = '\0';                                    
			                                
                                            if(insereLista(&l,palavra,linha,novaLinha))
                                                                       k++;  
										    novaLinha = 0; // pontuacao não deve ser inserido em uma nova linha             
										
										    if(insereLista(&l,pontuacao,linha,novaLinha))
										        if(frase[k] != '\n' && frase[k] == ' ' && !(ispunct(frase[k])))
												// incrementa k se o caractere for um espaço em branco depois de um sinal de pontuação
        													k++;
									}else{
                                      
										// o último caractere não é um sinal de pontuação;
									
										i -= k; // total de elementos da String palavra
										
										for(j = 0; j < i; j++)
                                            palavra[j] = frase[k++];
												
										palavra[j] = '\0';
                                    
										if(insereLista(&l,palavra,linha,novaLinha))
                                                                k++;                                    
									}	
									
									novaLinha = 0;	 // próximas palavras não serão inseridas em uma 
													 // nova linha								
							}	
							
							linha++;  // incrementa o total de linhas
							
							novaLinha = 1;	 // próximas palavras serão inseridas em uma 
											 // nova linha								
						}	
						
						linhaCorrente = linha - 1; // a linha corrente será inicialmente linha - 1
						
						// imprime a lista						
						i = 0;
						while(consultaLista(l,i,linhaCorrente) && i < linha)
					                            i++;
						 					
						puts("");
						fclose(f);
                    }else{
                            printf("\nO Arquivo %s nao existe!\n",nomeArquivo);
                            printf("\nCriando o Arquivo ...\n");
                                if((f = fopen(nomeArquivo,"w")) == NULL)
                                    printf("Erro na criacao de %s!\n",nomeArquivo); 
                                else {  
                                    printf("Arquivo criado com sucesso!\n\n");
								    fclose(f);
								}
                    }   
                    break; 
        
            case 'I':
					// Inserir Novas Linhas;
					
		            do{	
                        fgets(frase,99,stdin); // digita uma linha a partir do teclado
						
						// enquanto o primeiro caractere de frase for diferente de '$', ou seja,
						// não for um novo comando
                        if(frase[0] != '$'){
						
							novaLinha = 1; // indica a inserção de uma nova linha
							
							if(!listaVazia(l)) // caso a lista esteja vazia, a linha corrente
											   // permanece igual a zero
								linhaCorrente++; 
								
							k = 0;
							
							// enquanto o caractere não for '\n' nem k menor que o tamanho da String
							while(frase[k] != '\n' && k < strlen(frase)){
								i = k;
								while(frase[i] != ' ' && frase[i] != '\n' && (!ispunct(frase[i])) && i < strlen(frase))	
															i++;
                                                                               
								if(ispunct(frase[i])){ // o último caractere é um sinal de pontuação
								
									pontuacao[0] = frase[i];
									pontuacao[1] = '\0';
										
                                    i -= k;
                                    for(j = 0; j < i; j++)
                                        palavra[j] = frase[k++];
												
                                    palavra[j] = '\0';
                                    
                                    if(insereLista(&l,palavra,linhaCorrente,novaLinha))
                                                                k++;  
																
                                    novaLinha = 0; // pontuacao não deve ser inserido em uma nova linha                                
									
									if(insereLista(&l,pontuacao,linhaCorrente,novaLinha))
										if(frase[k] != '\n' && frase[k] == ' ' && !(ispunct(frase[k])))
										// incrementa k se o caractere for um espaço em branco depois de um sinal de pontuação
													k++;
															
                                }else{ // o último caractere não é um sinal de pontuação
								
                                    i -= k;
                                    for(j = 0; j < i; j++)
                                            palavra[j] = frase[k++];
												
                                    palavra[j] = '\0';
                                    
                                    if(insereLista(&l,palavra,linhaCorrente,novaLinha))
                                                                k++;                                
								}
								
								novaLinha = 0;	 // próximas palavras não serão inseridas em uma 
												// nova linha				
							}							
							linha++; // incrementa o total de linhas
							
                        }else{
							// novo comando;
							// verifica se o comando existe
							
                            if(comandoValido(frase)){
                                comandoInserir = 1; // sinaliza que um novo comando foi pedido e validado
								strcpy(op,frase); // copia frase em op(variável que armazena tanto 
												 // os comandos desejados)
								break;
								
                            }else{
                                puts("Comando Invalido!\n");
                                break;
								
                            }                                                   
                        }
						
                    }while(1);
					
                    break;         
                    
            case 'L':
					// Mudar a Linha Corrente;
					
					if(listaVazia(l))
						puts("Arquivo Vazio!!");
						
					else{					
						if(op[3] == '-'){ // verifica se foi digitado o comando $L -1
						
							// inserir linha na posição "-1", ou seja, antes da linha zero
							// armazena na String numero o caractere referente ao número digitado
							for(i = 0; i < strlen(op) && op[i+4] != '\0'; i++)
													numero[i] = op[i+4];
                    
							numero[i] = '\0';
							m = verificaNumero(numero); // converte o caractere em inteiro
							m *= -1; // novo valor de m(negativo)
							
							if(m != -1){ // caso m seja diferente de -1
								printf("Linha invalida!!\n");
								break;
							}else{
								fgets(op,99,stdin);
								
								// verifica se a opção digitada é "$I"
								if(op[0] == '$' && op[1] == 'I'){
									linhaCorrente = m; // nova linha corrente é "-1"
									comandoInserir = 1; // sinaliza o comando inserir
									break;
								}else{
									puts("Comando invalido!!\n");
									break;
								}
							}
						
						}else{
							
							// muda a linha para posição m
							// armazena na String numero o caractere referente ao número digitado							
							for(i = 0; i < strlen(op) && op[i+3] != '\0'; i++)
											numero[i] = op[i+3];
                    
							numero[i] = '\0';
							m = verificaNumero(numero);
                    
							if(m < 0 || m >= linha){ // se m for negativo ou maior que o total de linhas
								printf("Linha invalida!!!\n");
								break;
							}
                    
							i = 0;
							linhaCorrente = m; // a nova linha corrente é a linha m
							
							// imprime a lista	
							puts("");	
							while(consultaLista(l,i,m) && i < linha)
					                    i++;
								puts("");	
						}
					}	
					
					break;
			
			case 'S':			
					// Substituir ou Eliminar Palavras;
					
					if(op[3] == '^'){

							// armazena na String palavra a primeira palavra desejada
							for(i = 0; i < strlen(op) && op[i+4] != '^'; i++)
													palavra[i] = op[i+4];
                    
							palavra[i] = '\0';
							
							// certifica se o caractere '^' foi digitado
							if(op[i+4] == '^'){
							
									// verifica se o caractere foi digitado '^'
									if(op[i+5] == '^'){
                                               
										// opção para remover uma palavra da linha
										if(removePalavra(&l,palavra,linhaCorrente)){
													i = 0;			
													puts("");		
													while(consultaLista(l,i,linhaCorrente) && i < linha)
																			i++;
													puts("");
											break;
										}else
												puts("Palavra nao encontrada!");
									}else{	
											// opção para substituir uma palavra
											if(op[i+5] != '\0'){
												k = i+5;	
												
												// armazena na String substituta a segunda palavra desejada
												for(i = 0; i < strlen(op) && op[k] != '^'; i++)
														substituta[i] = op[k++];
                    
												substituta[i] = '\0';
												
												// certifica se o caractere '^' foi digitado
												if(op[k] != '^')
													puts("Omissao de delimitador!!");
												else{
													if(substituiPalavra(&l,palavra,substituta,linhaCorrente)){
																i = 0;			
																puts("");		
																while(consultaLista(l,i,linhaCorrente) && i < linha)
																				i++;
																puts("");
																break;
													}else
														puts("Palavra nao encontrada!");
												}
											
											// omissão de um caractere '^'		
											}else{
												puts("Comando invalido!!");	
											}
									}
									
							// omissão de um caractere '^'		
							}else
								puts("Omissao de delimitador!!");
								
					// omissão de um caractere '^'	
					}else
						puts("Omissao de delimitador!!");
						
					break;
			
			case 'U':
					// Mostrar o Número da Última Linha;
			
					i = 0;			
					puts("");	

					// imprime a lista	
					while(consultaLista(l,i,linhaCorrente) && i < linha)
					                             i++;
					
					// imprime o total de linhas, que representa o número da última linha	
				    printf("%d\n",l->nroLinhas);
					puts("");
				    break;
				                                    
			case 'R':
					// Remover um Intervalo de Linhas;
					
					if(valoresValidos(op, numero, &m, &n, l->nroLinhas)){ // verifica se os número digitados
																		 // são válidos
																		 
						int decrementaLinha = 0; // armazena o valor da linha n + 1
						
						if(m <= linhaCorrente && linhaCorrente <= n){ // se a linha corrente estiver no intervalo
							if(m - 1 >= 0) // se a linha m-1 existe
								linhaCorrente = m - 1;
							else{
								if(n + 1 < linha){ // se a linha n+1 existe
									linhaCorrente = n + 1;
									decrementaLinha = n + 1;
								}else{ // se o arquivo tiver apenas 2(duas) linhas
									linhaCorrente = 0;
								}
							} 
						}						
                    
						totalLinhas = n - m + 1; // total de linhas a serem eliminadas
						i = m;
					
						// remove as linhas da lista
						while(totalLinhas > 0){
							if(removerLinhas(&l,i)){
									totalLinhas--; // decrementa o total de linhas a serem eliminadas
								if(decrementaLinha == n + 1)
                                                linhaCorrente--; // se "m - 1" não existe decrementa a linha 
														        // corrente que representa a linha "n + 1"
																// a medida que se remove o total de linhas
								else{
									if(linhaCorrente != m-1)
											linhaCorrente--; // decrementa a linha corrente caso ela
															// não esteja no intervalo: m <= linhaCorrente <= n
								}
								linha--; // decrementa o total de linhas
							}
						}	
					
						i = 0;
						
						// imprime a lista
						puts("");	
						while(consultaLista(l,i,linhaCorrente) && i < linha)
					                             i++;
						puts("");	
					}
	                break;
				                                    
			case 'M':
					// Mostrar um Intervalo de Linhas;
			
					if(valoresValidos(op, numero, &m, &n, l->nroLinhas)){ // verifica se os número digitados
																		 // são válidos
                                  
						totalLinhas = n - m + 1;// total de linhas a serem impressas
						i = m;
						
						// enquanto o total de linhas a serem impressas for maior que zero,
						// e a linha inicial "m' for menor ou igual a linha "n"
						while(totalLinhas > 0 && i <= n){
							if(imprimeIntervalo(l,i)){
									totalLinhas--; // decrementa o total de linhas a serem impressas
								i++;
							}		
						}
						puts("");	
					}
	                break;                        
                        
            case 'F':
					// Fechar um Arquivo;
			
					nomeDoArquivo(nomeArquivo,op); // chama a função para salvar o nome do arquivo
                    
                    if((f = fopen(nomeArquivo,"w")) != NULL){
                            i = 0;
					        while(i < linha)
								// salva todas as linhas no arquivo
					            if(abreLista(l,i,f,linha - 1))
					                        i++;
                            printf("Arquivo salvo com sucesso!!!!!!\n");
					
                            fclose(f);
                    } 
				    sair = 1; // sinaliza a saída do programa
				    break;
					
	         default: 
					puts("Comando invalido!!");
	                break;
        }   
		
    }while(sair == 0);	
	
    system("pause");
    return 0;    
}
