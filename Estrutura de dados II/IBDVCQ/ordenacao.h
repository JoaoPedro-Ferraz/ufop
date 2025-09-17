#ifndef ORDENACAO_H
#define ORDENACAO_H

#include "leituraArquivo.h"  


void quickSort(Aluno *v, int tam, int *);


void quickRec(Aluno *v, int p, int r, int *);
void troca(Aluno *a, Aluno *b);

#endif 
