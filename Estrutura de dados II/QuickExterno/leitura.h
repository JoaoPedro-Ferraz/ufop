#ifndef LEITURA_H
#define LEITURA_H

#include "registro.h"


int carregarRegistros(const char *nomeArquivo, Registro *vetor, int n);


void salvarRegistros(const char *nomeArquivo, Registro *vetor, int n);


void gerarArquivoOrdenado(const char *entrada, const char *saida, int n, int modo);

int contar_registros(char *arquivo);


#endif 
