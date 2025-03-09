#include <stdio.h>
#include <stdlib.h>
#include "instrucao.h"

// Função para carregar as instruções de um arquivo no formato correto
Instrucao* carregarInstrucoes(const char *nomeArquivo, int *numInstrucoes) {
    FILE *file = fopen(nomeArquivo, "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo de instruções!\n");
        exit(1);
    }

    int capacidade = 100;  // Capacidade inicial de instruções
    *numInstrucoes = 0;
    Instrucao *programa = (Instrucao*) malloc(capacidade * sizeof(Instrucao));

    char linha[100];  // Buffer para cada linha do arquivo
    while (fgets(linha, sizeof(linha), file)) {
        if (*numInstrucoes == capacidade) {
            capacidade *= 2;
            programa = (Instrucao*) realloc(programa, capacidade * sizeof(Instrucao));
        }

        Instrucao inst;
        // Parse da linha no formato "opcode:add1Bloco:add1Palavra:add2Bloco:add2Palavra:add3Bloco:add3Palavra"
        sscanf(linha, "%d:%d:%d:%d:%d:%d:%d",
               &inst.opcode,
               &inst.add1.endBloco, &inst.add1.endPalavra,
               &inst.add2.endBloco, &inst.add2.endPalavra,
               &inst.add3.endBloco, &inst.add3.endPalavra);

        programa[*numInstrucoes] = inst;
        (*numInstrucoes)++;
    }

    fclose(file);
    return programa;
}
