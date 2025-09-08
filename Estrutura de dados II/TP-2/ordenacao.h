#ifndef ORDENACAO_H
#define ORDENACAO_H

#include "leituraArquivo.h"  // para a definição da struct Aluno

// Função pública para ordenar um vetor de Aluno por nota
void quickSort(Aluno *v, int tam);

// Declarações das funções auxiliares (podem ser usadas para evitar warnings)
void quickRec(Aluno *v, int p, int r);
void troca(Aluno *a, Aluno *b);

#endif // ORDENACAO_H
