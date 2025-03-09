#include <stdio.h>
#include <stdlib.h>
#include "instrucao.h"
#include "mmu.h"
#include <time.h>
#include <string.h>

// Defina o número de conjuntos (exemplo com 4 conjuntos e associatividade de 2 linhas por conjunto)
#define NUM_CONJUNTOS 4
#define LINHAS_POR_CONJUNTO 2

// Função para buscar um bloco nas memórias (cache1, cache2, cache3, e RAM)
BlocoMemoria buscarNasMemorias(Endereco *e, RAM *ram, BlocoMemoria *cache1, int tamCache1, BlocoMemoria *cache2, int tamCache2, BlocoMemoria *cache3, int tamCache3, char *politica) {
    // Calcula o conjunto do bloco nas caches usando o número de conjuntos
    int conjuntoCache1 = e->endBloco % NUM_CONJUNTOS;  // Conjunto na Cache 1
    int conjuntoCache2 = e->endBloco % NUM_CONJUNTOS;  // Conjunto na Cache 2
    int conjuntoCache3 = e->endBloco % NUM_CONJUNTOS;  // Conjunto na Cache 3

    // Verifica se o bloco está em cache1 (hit cache 1)
    for (int i = 0; i < LINHAS_POR_CONJUNTO; i++) {
        int posicaoCache1 = conjuntoCache1 * LINHAS_POR_CONJUNTO + i;
        if (cache1[posicaoCache1].endBloco == e->endBloco) {
            cache1[posicaoCache1].custo = 10;  // Custo de acessar o cache 1
            cache1[posicaoCache1].cacheHit = 1;  // Hit no cache 1
            cache1[posicaoCache1].lastUsed = time(NULL);  // Atualiza o tempo para LRU
            cache1[posicaoCache1].frequency++;  // Incrementa a frequência para LFU
            return cache1[posicaoCache1];  // Retorna o bloco encontrado no cache 1
        }
    }

    // Verifica se o bloco está em cache2 (miss cache 1, hit cache 2)
    for (int i = 0; i < LINHAS_POR_CONJUNTO; i++) {
        int posicaoCache2 = conjuntoCache2 * LINHAS_POR_CONJUNTO + i;
        if (cache2[posicaoCache2].endBloco == e->endBloco) {
            cache2[posicaoCache2].custo = 110;  // Custo de acessar o cache 2
            cache2[posicaoCache2].cacheHit = 2;  // Hit no cache 2
            cache2[posicaoCache2].lastUsed = time(NULL);  // Atualiza o tempo para LRU
            cache2[posicaoCache2].frequency++;  // Incrementa a frequência para LFU
            return movCache2Cache1(conjuntoCache1, posicaoCache2, cache1, cache2, 110);  // Move para cache 1 e retorna
        }
    }

    // Verifica se o bloco está em cache3 (miss cache 1 e cache 2, hit cache 3)
    for (int i = 0; i < LINHAS_POR_CONJUNTO; i++) {
        int posicaoCache3 = conjuntoCache3 * LINHAS_POR_CONJUNTO + i;
        if (cache3[posicaoCache3].endBloco == e->endBloco) {
            cache3[posicaoCache3].custo = 1110;  // Custo de acessar o cache 3
            cache3[posicaoCache3].cacheHit = 3;  // Hit no cache 3
            cache3[posicaoCache3].lastUsed = time(NULL);  // Atualiza o tempo para LRU
            cache3[posicaoCache3].frequency++;  // Incrementa a frequência para LFU
            return movCache3Cache1(conjuntoCache1, conjuntoCache2, posicaoCache3, cache1, cache2, cache3, 1110);  // Move para cache 1 e retorna
        }
    }

    // Se não estiver em nenhuma cache, busca na RAM (miss em todas as caches)
    BlocoMemoria blocoRAM = ram->memoria[e->endBloco];  // Busca o bloco na RAM
    blocoRAM.custo = 11110;  // Custo de acessar a RAM
    blocoRAM.cacheHit = 4;  // Miss em todas as caches
    // Move o bloco da RAM para cache 3 e retorna
    return movRamCache3(conjuntoCache1, conjuntoCache2, conjuntoCache3, cache1, cache2, cache3, ram, e, blocoRAM.custo, politica);
}

// Movimenta um bloco do cache2 para o cache1
BlocoMemoria movCache2Cache1(int conjuntoCache1, int posicaoCache2, BlocoMemoria *cache1, BlocoMemoria *cache2, int custo) {
    int posicaoCache1 = conjuntoCache1 * LINHAS_POR_CONJUNTO + findLRU(cache1, conjuntoCache1);
    BlocoMemoria aux = cache1[posicaoCache1];
    cache1[posicaoCache1] = cache2[posicaoCache2];  // Manda o bloco do cache2 para o cache1
    cache2[posicaoCache2] = aux;  // Manda o bloco do cache1 para o cache2
    cache1[posicaoCache1].custo = custo;
    return cache1[posicaoCache1];
}

// Movimenta um bloco do cache3 para o cache1, passando por cache2
BlocoMemoria movCache3Cache1(int conjuntoCache1, int conjuntoCache2, int posicaoCache3, BlocoMemoria *cache1, BlocoMemoria *cache2, BlocoMemoria *cache3, int custo) {
    int posicaoCache1 = conjuntoCache1 * LINHAS_POR_CONJUNTO + findLRU(cache1, conjuntoCache1);
    int posicaoCache2 = conjuntoCache2 * LINHAS_POR_CONJUNTO + findLRU(cache2, conjuntoCache2);
    BlocoMemoria aux = cache1[posicaoCache1];
    cache1[posicaoCache1] = cache3[posicaoCache3];  // Manda o bloco do cache3 para o cache1
    cache3[posicaoCache3] = cache2[posicaoCache2];  // Manda o bloco do cache2 para o cache3
    cache2[posicaoCache2] = aux;  // Manda o bloco do cache1 para o cache2
    cache1[posicaoCache1].custo = custo;
    return cache1[posicaoCache1];
}

// Movimenta um bloco da RAM para o cache3, depois cache2, depois cache1
BlocoMemoria movRamCache3(int conjuntoCache1, int conjuntoCache2, int conjuntoCache3, BlocoMemoria *cache1, BlocoMemoria *cache2, BlocoMemoria *cache3, RAM *ram, Endereco *e, int custo, char *politica) {
    int indexCache3 = (strcmp(politica, "LRU") == 0) ? findLRU(cache3, conjuntoCache3) : findLFU(cache3, conjuntoCache3);

    if (!cache3[indexCache3].atualizado) {
        cache3[indexCache3] = getDado(ram, e->endBloco);
        cache3[indexCache3].cacheHit = 4;
        return movCache3Cache1(conjuntoCache1, conjuntoCache2, indexCache3, cache1, cache2, cache3, custo);
    } else {
        cache3[indexCache3].atualizado = 0;
        setDado(ram, cache3[indexCache3].endBloco, cache3[indexCache3]);
        cache3[indexCache3] = getDado(ram, e->endBloco);
        cache3[indexCache3].cacheHit = 4;
        return movCache3Cache1(conjuntoCache1, conjuntoCache2, indexCache3, cache1, cache2, cache3, custo);
    }
}

// Encontra o bloco menos usado (LRU) dentro de um conjunto
int findLRU(BlocoMemoria *cache, int conjunto) {
    long oldest = time(NULL);
    int index = 0;
    for (int i = conjunto * LINHAS_POR_CONJUNTO; i < (conjunto + 1) * LINHAS_POR_CONJUNTO; i++) {
        if (cache[i].lastUsed < oldest) {
            oldest = cache[i].lastUsed;
            index = i;
        }
    }
    return index;
}

// Encontra o bloco menos frequentemente usado (LFU) dentro de um conjunto
int findLFU(BlocoMemoria *cache, int conjunto) {
    int leastFreq = cache[conjunto * LINHAS_POR_CONJUNTO].frequency;
    int index = conjunto * LINHAS_POR_CONJUNTO;
    for (int i = conjunto * LINHAS_POR_CONJUNTO + 1; i < (conjunto + 1) * LINHAS_POR_CONJUNTO; i++) {
        if (cache[i].frequency < leastFreq) {
            leastFreq = cache[i].frequency;
            index = i;
        }
    }
    return index;
}
