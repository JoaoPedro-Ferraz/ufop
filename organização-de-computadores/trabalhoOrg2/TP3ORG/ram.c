#include <stdio.h>
#include <stdlib.h>
#include "ram.h"

RAM* criarRAM_aleatoria(int tamanho) {
    RAM *ram = (RAM*) malloc(sizeof(RAM));
    ram->memoria = (BlocoMemoria*) malloc(tamanho * sizeof(BlocoMemoria));
    ram->tamanho = tamanho;

    for (int i = 0; i < tamanho; i++) {
        ram->memoria[i].endBloco = i;
        for (int j = 0; j < 4; j++) {
            ram->memoria[i].palavras[j] = rand()%1000+1;  // Valores aleatórios
        }
    }

    return ram;
}

BlocoMemoria getDado(RAM *ram, int endereco) {
    return ram->memoria[endereco];
}

void setDado(RAM *ram, int endereco, BlocoMemoria conteudo) {
    ram->memoria[endereco] = conteudo;
}

void imprimirRAM(RAM *ram) {
    printf("Conteúdo da RAM:\n");
    for (int i = 0; i < ram->tamanho; i++) {
        for (int j = 0; j < 4; j++) {
            printf("%d ", ram->memoria[i].palavras[j]);
        }
        printf("\n");
    }
}

void carregarMemoriaExterna(const char *nomeArquivo, BlocoMemoria *bloco, int endereco) {
    FILE *file = fopen(nomeArquivo, "rb");
    if (file) {
        fseek(file, endereco * sizeof(BlocoMemoria), SEEK_SET);
        fread(bloco, sizeof(BlocoMemoria), 1, file);
        fclose(file);
    }
}

void salvarMemoriaExterna(const char *nomeArquivo, BlocoMemoria *bloco, int endereco) {
    FILE *file = fopen(nomeArquivo, "r+b");
    if (!file) {
        file = fopen(nomeArquivo, "wb");
    }
    fseek(file, endereco * sizeof(BlocoMemoria), SEEK_SET);
    fwrite(bloco, sizeof(BlocoMemoria), 1, file);
    fclose(file);
}
