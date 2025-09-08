#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "leituraArquivo.h"

#define maxTam 256 // tamanho suficiente para linha inteira

void verificacaoAbertura(FILE *arquivo) {
    if (arquivo != NULL) return;
    fprintf(stderr, "Erro ao abrir arquivo!\n");
    exit(EXIT_FAILURE);
}

// Leitura de bloco
int leituraDados(FILE *arquivo, Aluno *vetorDados) {
    char dadosLinha[maxTam], temp[50];
    int i = 0;
    
    while(i < memorysize) {
        if(fgets(dadosLinha, maxTam, arquivo) == NULL)
            break;

        // Ignora linhas vazias ou incompletas
        if(strlen(dadosLinha) < 70) {
            continue;
        }

        // Remove \n no final da linha
        dadosLinha[strcspn(dadosLinha, "\n")] = '\0';

        // Numero de inscricao
        strncpy(temp, dadosLinha, 8);
        temp[8] = '\0';
        strcpy(vetorDados[i].inscricao, temp);

        // Nota 
        strncpy(temp, dadosLinha + 9, 5);
        temp[5] = '\0';
        vetorDados[i].nota = strtof(temp, NULL);

        // Estado 
        strncpy(vetorDados[i].estado, dadosLinha + 15, 2);
        vetorDados[i].estado[2] = '\0';

        // Cidade 
        strncpy(vetorDados[i].cidade, dadosLinha + 18, 50);
        vetorDados[i].cidade[50] = '\0';

        // Curso 
        strncpy(vetorDados[i].curso, dadosLinha + 69, 30);
        vetorDados[i].curso[30] = '\0';
        
        i++;
    }
    return i;
}


bool readAlunoLine(FILE *arquivo, Aluno *a) {
    char dadosLinha[maxTam], temp[64];

    if (fgets(dadosLinha, maxTam, arquivo) == NULL)
        return false;

    // Numero de inscricao
    memcpy(temp, dadosLinha, 8);
    temp[8] = '\0';
    strncpy(a->inscricao, temp, 9);
    a->inscricao[8] = '\0';

    // Nota
    memcpy(temp, dadosLinha + 9, 5);
    temp[5] = '\0';
    a->nota = strtof(temp, NULL);

    // Estado
    memcpy(temp, dadosLinha + 15, 2);
    temp[2] = '\0';
    strncpy(a->estado, temp, 3);
    a->estado[2] = '\0';

    // Cidade
    memcpy(temp, dadosLinha + 18, 50);
    temp[50] = '\0';
    for (int k = 49; k >= 0 && temp[k] == ' '; k--) temp[k] = '\0';
    strncpy(a->cidade, temp, MAX_CIDADE + 1);
    a->cidade[MAX_CIDADE] = '\0';

    // Curso
    memcpy(temp, dadosLinha + 69, 30);
    temp[30] = '\0';
    for (int k = 29; k >= 0 && temp[k] == ' '; k--) temp[k] = '\0';
    strncpy(a->curso, temp, MAX_CURSO + 1);
    a->curso[MAX_CURSO] = '\0';

    return true;
}

//Gravacao de aluno no arquivo correspondente
void escreveAluno(FILE *arquivo, const Aluno *a) {
    fprintf(arquivo, "%-8s %05.1f %-2s %-50s %-30s\n",
            a->inscricao,
            a->nota,
            a->estado,
            a->cidade,
            a->curso);
}