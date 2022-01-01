# text-editor

Text editor in C language

## Commands

```bash
$A nomeArquivo.extensao ---------------------------- Abrir/Criar um Arquivo
$I ------------------------- Insere novas linhas a partir da linha corrente
$L m --------------------------------- Muda a linha corrente para a linha m
$L -1 <enter> $I ------------------ Insere antes da primeira linha do texto
$S ^x^y^ ------- Substitui a sequencia x pela sequencia y na linha corrente
$S ^x^^ --------------------------- Elimina a sequencia x na linha corrente
$U ---------------------------------------- Mostra o numero da ultima linha
$R m,n ----------------------------- Remover linhas entre o intervalo "m" e "n"
$M m,n --------------------------- Mostra as linhas entre o intervalo "m" e "n"
$F nomeArquivo.extensao ----------------- Fechar o Editor e Salva o Arquivo
```
