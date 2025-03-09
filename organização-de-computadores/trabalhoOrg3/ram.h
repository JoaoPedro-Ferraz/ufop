#ifndef RAM_H
#define RAM_H

#include "bloco_memoria.h"

typedef struct {
    BlocoMemoria *memoria;
    int tamanho;
} RAM;

RAM* criarRAM_aleatoria(int tamanho);
BlocoMemoria getDado(RAM *ram, int endereco);
void setDado(RAM *ram, int endereco, BlocoMemoria conteudo);
void imprimirRAM(RAM *ram);
void carregarMemoriaExterna(const char *nomeArquivo, BlocoMemoria *bloco, int endereco);
void salvarMemoriaExterna(const char *nomeArquivo, BlocoMemoria *bloco, int endereco);

#endif
