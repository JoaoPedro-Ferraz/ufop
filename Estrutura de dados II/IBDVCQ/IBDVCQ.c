#define _POSIX_C_SOURCE 199309L 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "leituraArquivo.h"

#include "IBDVC.h"

static void IBDVC_QUICK(FILE *arquivo) {
    
    struct timespec t_inicio, t_fim; 

    
    clock_gettime(CLOCK_MONOTONIC, &t_inicio);
    
    int escrita = 0, leitura = 0, comparacoes = 0;

    
    startIntercalacao(arquivo, &leitura, &escrita, &comparacoes); 

    
    clock_gettime(CLOCK_MONOTONIC, &t_fim); 

    
    unsigned long long inicio_ns = t_inicio.tv_sec * 1000000000ULL + t_inicio.tv_nsec;
    unsigned long long fim_ns    = t_fim.tv_sec    * 1000000000ULL + t_fim.tv_nsec;
    unsigned long long tempo_ns  = fim_ns - inicio_ns;

    printf("Tempo total de execucao: %.6f segundos\nLeituras: %d\nEscritas: %d\nComparacoes: %d\n", tempo_ns / 1e9, leitura, escrita, comparacoes);

    return 0;
}