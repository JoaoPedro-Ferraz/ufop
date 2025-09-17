#ifndef IBDVC_H 
#define IBDVC_H

#include "leituraArquivo.h"


#define NUM_FITAS 40


void startIntercalacao(char *, int *, int *, int *); 
void copiaArquivo(char *, char *);
int cmpAlunoRun(Aluno *, Aluno *);
int faseIntercalacaoList(char **, char **, int, int, int *, int *, int *);

#endif 
