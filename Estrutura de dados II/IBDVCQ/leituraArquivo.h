#ifndef LEITURAARQUIVO_H
#define LEITURAARQUIVO_H

#include <stdio.h>
#include <stdbool.h>

#define memorysize 20   
#define MAX_CIDADE 50
#define MAX_CURSO 30

typedef struct {
    char inscricao[9];        
    float nota;                 
    char estado[3];             
    char cidade[MAX_CIDADE+1];  
    char curso[MAX_CURSO+1];
} Aluno;




int leituraDados(FILE *, Aluno *, int *);

bool readAlunoLine(FILE *, Aluno *, int *); 

void escreveAluno(FILE *, Aluno *, int *);

void verificacaoAbertura(FILE *);

#endif 