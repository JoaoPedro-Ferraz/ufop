#ifndef CPU_H
#define CPU_H

#include "ram.h"
#include "instrucao.h"

typedef struct {
    BlocoMemoria *cache1;
    BlocoMemoria *cache2;
    BlocoMemoria *cache3;
    int hitC1, missC1, hitC2, missC2, hitC3, missC3;
    int tempoTotal;
    Instrucao *programa;
    int PC;
    int opcode;
    BlocoMemoria registrador1, registrador2, registrador3;
    int interrupcao; // Variável para controlar interrupções

    // Variáveis para salvar o contexto durante a interrupção
    int contexto_PC;  // Contador de programa salvo
    BlocoMemoria contexto_registrador1;
    BlocoMemoria contexto_registrador2;
    BlocoMemoria contexto_registrador3;

} CPU;

CPU* inicializarCPU(int tamCache1, int tamCache2, int tamCache3);
void executarPrograma(CPU *cpu, RAM *ram, char *politica,int tam1,int tam2,int tam3);
void tratadorDeInterrupcao(CPU *cpu, RAM *ram);
void liberarCPU(CPU *cpu);


#endif
