#include <stdio.h>
#include "metrica.h"

void iniciar_metricas(Metricas *m) {
    m->comparacoes = 0;
    m->leituras = 0;
    m->escritas = 0;
    m->inicio = clock();
}

void finalizar_metricas(Metricas *m) {
    m->fim = clock();
}

void imprimir_metricas(const Metricas *m) {
    double tempo = (double)(m->fim - m->inicio) / CLOCKS_PER_SEC;

    printf("\n----- MÉTRICAS -----\n");
    printf("Comparações: %ld\n", m->comparacoes);
    printf("Leituras:    %ld\n", m->leituras);
    printf("Escritas:    %ld\n", m->escritas);
    printf("Tempo:       %.4f segundos\n", tempo);
    printf("---------------------\n");
}

void contar_comparacao(Metricas *m) {
    m->comparacoes++;
}

void contar_leitura(Metricas *m) {
    m->leituras++;
}

void contar_escrita(Metricas *m) {
    m->escritas++;
}
