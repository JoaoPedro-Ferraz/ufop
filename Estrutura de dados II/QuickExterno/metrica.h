#ifndef METRICAS_H
#define METRICAS_H

#include <time.h>

typedef struct {
    long comparacoes;
    long leituras;
    long escritas;
    clock_t inicio;
    clock_t fim;
} Metricas;


void iniciar_metricas(Metricas *m);

void finalizar_metricas(Metricas *m);

void imprimir_metricas(const Metricas *m);

void contar_comparacao(Metricas *m);

void contar_leitura(Metricas *m);

void contar_escrita(Metricas *m);

#endif 
