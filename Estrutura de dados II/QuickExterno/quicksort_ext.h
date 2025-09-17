#ifndef QUICKSORT_EXT_H
#define QUICKSORT_EXT_H

#include "registro.h"
#include "metrica.h" 
#include "leitura.h"



void quicksort_externo(char *arquivo, int quantidade, int situacao, int imprime);


void quicksort_externo_recursivo(char *arquivo, int situacao, Metricas *stats);


void particionar_arquivo(char *arquivo_entrada, char *arquivo_menores, char *arquivo_maiores, float pivo, Metricas *stats);


float selecionar_pivo(char *arquivo, int situacao, Metricas *stats);


void mesclar_arquivos(char *arquivo_saida, char *arquivo1, char *arquivo2, int situacao, Metricas *stats);


void troca(Registro *a, Registro *b, Metricas *stats);


void limpar_arquivos_temporarios();

#endif 
