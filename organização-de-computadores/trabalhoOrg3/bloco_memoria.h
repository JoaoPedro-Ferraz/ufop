#ifndef BLOCO_MEMORIA_H
#define BLOCO_MEMORIA_H

typedef struct {
    int palavras[4];  // Cada bloco tem 4 palavras
    int endBloco;     // Endereço do bloco
    int atualizado;   // Indica se o bloco foi atualizado
    int custo;        // Custo da operação
    int cacheHit;     // Indica se o bloco foi hit no cache (1, 2, 3)
    long lastUsed;    // Para LRU (timestamp do último uso)
    int frequency;    // Para LFU (frequência de uso)
} BlocoMemoria;

#endif
