#ifndef ARVORE_BINARIA_H
#define ARVORE_BINARIA_H

#include <stdio.h>

/*
 - No da arvore binaria armazenada em disco.
 - Os campos 'esquerda' e 'direita' simulam os ponteiros, usando posicoes do arquivo.
 */
typedef struct {
    int chave;
    long dado1;
    char dado2[5000];
    int esquerda, direita; // Posicoes dos filhos no arquivo
    int indice;            // Posicao do no no arquivo
} NoArvore;

/*
 - Atualiza a ligacao entre um novo no (filho) e o no pai, conforme a chave.
 - O no pai e encontrado dinamicamente a partir da raiz.
 */
void ajustarLigacaoPaiFilho(int posFilho, FILE *arquivo, int *acessos, int *comparacoes);

/*
 - Realiza a busca de uma chave na arvore binaria armazenada no arquivo.
 - Retorna a chave se encontrada, ou -1 caso contrario.
 */
int buscarNaArvore(int chave, FILE *arquivo, int *acessos, int *comparacoes);

void inserirNaArvore(FILE *arquivo, int posAtual, int posNovo, int *acessos, int *comparacoes);

#endif