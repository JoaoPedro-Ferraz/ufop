#ifndef LEITURAARQUIVOSB_H
#define LEITURAARQUIVOSB_H

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



int leituraDadosSB(FILE *arquivo, Aluno *vetorDados);



int readAlunoLineSB(FILE *arquivo, Aluno *a);


void escreveAlunoSB(FILE *arquivo, const Aluno *a);


void verificacaoAberturaSB(FILE *arquivo);

#endif 
