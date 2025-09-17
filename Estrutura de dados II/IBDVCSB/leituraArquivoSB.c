#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "leituraArquivoSB.h"

#define maxTam 256 

extern long long leituras;
extern long long escritas;

void verificacaoAberturaSB(FILE *arquivo) {
    if (arquivo != NULL) return;
    fprintf(stderr, "Erro ao abrir arquivo!\n");
    exit(EXIT_FAILURE);
}

int leituraDadosSB(FILE *arquivo, Aluno *vetorDados) {
    char dadosLinha[maxTam], temp[50];
    int i = 0;

    while (i < memorysize) {
        if (fgets(dadosLinha, maxTam, arquivo) == NULL)
            break;

        if (strlen(dadosLinha) < 70) {
            continue;
        }

        dadosLinha[strcspn(dadosLinha, "\n")] = '\0';

        strncpy(temp, dadosLinha, 8);
        temp[8] = '\0';
        strcpy(vetorDados[i].inscricao, temp);

        strncpy(temp, dadosLinha + 9, 5);
        temp[5] = '\0';
        vetorDados[i].nota = strtof(temp, NULL);

        strncpy(vetorDados[i].estado, dadosLinha + 15, 2);
        vetorDados[i].estado[2] = '\0';

        strncpy(vetorDados[i].cidade, dadosLinha + 18, 50);
        vetorDados[i].cidade[50] = '\0';

        strncpy(vetorDados[i].curso, dadosLinha + 69, 30);
        vetorDados[i].curso[30] = '\0';

        i++;
    }
    return i;
}

int readAlunoLineSB(FILE *arquivo, Aluno *a) {
    char dadosLinha[maxTam], temp[64];

    if (fgets(dadosLinha, maxTam, arquivo) == NULL)
        return 0;

    memcpy(temp, dadosLinha, 8);
    temp[8] = '\0';
    strncpy(a->inscricao, temp, 9);
    a->inscricao[8] = '\0';

    memcpy(temp, dadosLinha + 9, 5);
    temp[5] = '\0';
    a->nota = strtof(temp, NULL);

    memcpy(temp, dadosLinha + 15, 2);
    temp[2] = '\0';
    strncpy(a->estado, temp, 3);
    a->estado[2] = '\0';

    memcpy(temp, dadosLinha + 18, 50);
    temp[50] = '\0';
    for (int k = 49; k >= 0 && temp[k] == ' '; k--) temp[k] = '\0';
    strncpy(a->cidade, temp, MAX_CIDADE + 1);
    a->cidade[MAX_CIDADE] = '\0';

    memcpy(temp, dadosLinha + 69, 30);
    temp[30] = '\0';
    for (int k = 29; k >= 0 && temp[k] == ' '; k--) temp[k] = '\0';
    strncpy(a->curso, temp, MAX_CURSO + 1);
    a->curso[MAX_CURSO] = '\0';

    return 1;
}

void escreveAlunoSB(FILE *arquivo, const Aluno *a) {
    fprintf(arquivo, "%-8s %05.1f %-2s %-50s %-30s\n",
            a->inscricao,
            a->nota,
            a->estado,
            a->cidade,
            a->curso);
    escritas++; 
}
