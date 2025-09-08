#ifndef LEITURAARQUIVO_H
#define LEITURAARQUIVO_H

#include <stdio.h>
#include <stdbool.h>

#define memorysize 4   //Representacao da memoria principal
#define MAX_CIDADE 50
#define MAX_CURSO 30

typedef struct {
    char inscricao[9];        
    float nota;                 
    char estado[3];             
    char cidade[MAX_CIDADE+1];  
    char curso[MAX_CURSO+1];
} Aluno;


//Funcoes
//Realiza leitura do bloco
int leituraDados(FILE *arquivo, Aluno *vetorDados);
//le uma linha formatada e preenche Aluno
bool readAlunoLine(FILE *arquivo, Aluno *a); 
// escreve um aluno no arquivo
void escreveAluno(FILE *arquivo, const Aluno *a);
// verifica abertura (termina o programa se falhar)
void verificacaoAbertura(FILE *arquivo);

#endif // LEITURAARQUIVO_H