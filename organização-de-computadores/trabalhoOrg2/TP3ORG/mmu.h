#ifndef MMU_H
#define MMU_H

#include "ram.h"

BlocoMemoria buscarNasMemorias(Endereco *e, RAM *ram, BlocoMemoria *cache1, int tamCache1, BlocoMemoria *cache2, int tamCache2, BlocoMemoria *cache3, int tamCache3, char *politica);
BlocoMemoria movCache2Cache1(int posicaoCache1, int posicaoCache2, BlocoMemoria *cache1, BlocoMemoria *cache2, int custo);
BlocoMemoria movCache3Cache1(int posicaoCache1, int posicaoCache2, int posicaoCache3, BlocoMemoria *cache1, BlocoMemoria *cache2, BlocoMemoria *cache3, int custo);
BlocoMemoria movRamCache3(int posicaoCache1, int posicaoCache2, int posicaoCache3, BlocoMemoria *cache1, BlocoMemoria *cache2, BlocoMemoria *cache3, RAM *ram, Endereco *e, int custo, char *politica);
void moverExternaParaRam(RAM *ram, const char *nomeArquivo, int enderecoBloco);

int findLRU(BlocoMemoria *cache, int tamanho);
int findLFU(BlocoMemoria *cache, int tamanho);

#endif
