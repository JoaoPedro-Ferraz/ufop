#include <stdio.h>
#include <stdlib.h>
#include "cpu.h"
#include "mmu.h"

CPU* inicializarCPU(int tamCache1, int tamCache2, int tamCache3) {
    CPU *cpu = (CPU*) malloc(sizeof(CPU));
    cpu->cache1 = (BlocoMemoria*) malloc(tamCache1 * sizeof(BlocoMemoria));
    cpu->cache2 = (BlocoMemoria*) malloc(tamCache2 * sizeof(BlocoMemoria));
    cpu->cache3 = (BlocoMemoria*) malloc(tamCache3 * sizeof(BlocoMemoria));

    // Inicializar os caches com blocos vazios
    for (int i = 0; i < tamCache1; i++) {
        cpu->cache1[i].endBloco = -1;  // Bloco vazio
    }
    for (int i = 0; i < tamCache2; i++) {
        cpu->cache2[i].endBloco = -1;
    }
    for (int i = 0; i < tamCache3; i++) {
        cpu->cache3[i].endBloco = -1;
    }

    cpu->hitC1 = cpu->missC1 = cpu->hitC2 = cpu->missC2 = cpu->hitC3 = cpu->missC3 = 0;
    cpu->tempoTotal = 0;
    cpu->PC = 0;
    return cpu;
}

void executarPrograma(CPU *cpu, RAM *ram, char *politica, int tam1, int tam2, int tam3) {
    while (1) {
        Instrucao inst = cpu->programa[cpu->PC];
        cpu->opcode = inst.opcode;

        if (cpu->opcode == -1) {
            printf("\nPrograma finalizado.\n");
            break;
        }

        // Buscar os blocos nas memórias
        cpu->registrador1 = buscarNasMemorias(&inst.add1, ram, cpu->cache1, tam1, cpu->cache2, tam2, cpu->cache3, tam3, politica);;
        cpu->registrador2 = buscarNasMemorias(&inst.add2, ram, cpu->cache1, tam1, cpu->cache2, tam2, cpu->cache3, tam3, politica);
        cpu->registrador3 = buscarNasMemorias(&inst.add3, ram, cpu->cache1, tam1, cpu->cache2, tam2, cpu->cache3, tam3, politica);

        // Atualizar o tempo total de execução com base nos custos de acesso
        cpu->tempoTotal += cpu->registrador1.custo;
        cpu->tempoTotal += cpu->registrador2.custo;
        cpu->tempoTotal += cpu->registrador3.custo;

        // Atualizar contadores de hits e misses para registrador 1
        switch (cpu->registrador1.cacheHit) {
            case 1:
                cpu->hitC1++;
                break;
            case 2:
                cpu->missC1++;
                cpu->hitC2++;
                break;
            case 3:
                cpu->missC1++;
                cpu->missC2++;
                cpu->hitC3++;
                break;
            case 4:
                cpu->missC1++;
                cpu->missC2++;
                cpu->missC3++;
                break;
        }

        // Atualizar contadores de hits e misses para registrador 2
        switch (cpu->registrador2.cacheHit) {
            case 1:
                cpu->hitC1++;
                break;
            case 2:
                cpu->missC1++;
                cpu->hitC2++;
                break;
            case 3:
                cpu->missC1++;
                cpu->missC2++;
                cpu->hitC3++;
                break;
            case 4:
                cpu->missC1++;
                cpu->missC2++;
                cpu->missC3++;
                break;
        }

        // Atualizar contadores de hits e misses para registrador 3
        switch (cpu->registrador3.cacheHit) {
            case 1:
                cpu->hitC1++;
                break;
            case 2:
                cpu->missC1++;
                cpu->hitC2++;
                break;
            case 3:
                cpu->missC1++;
                cpu->missC2++;
                cpu->hitC3++;
                break;
            case 4:
                cpu->missC1++;
                cpu->missC2++;
                cpu->missC3++;
                break;
        }

        // Realizar a operação
        switch (cpu->opcode) {
            case 0:  // Soma
                cpu->registrador3.palavras[inst.add3.endPalavra] =
                    cpu->registrador1.palavras[inst.add1.endPalavra] + cpu->registrador2.palavras[inst.add2.endPalavra];
                cpu->registrador3.atualizado = 1;
                printf("Soma -> RAM posicao %d com resultado %d (%d + %d)\n", inst.add3.endBloco, cpu->registrador3.palavras[inst.add3.endPalavra], cpu->registrador1.palavras[inst.add1.endPalavra],cpu->registrador2.palavras[inst.add2.endPalavra] );
                break;

            case 1:  // Subtração
                cpu->registrador3.palavras[inst.add3.endPalavra] =
                    cpu->registrador1.palavras[inst.add1.endPalavra] - cpu->registrador2.palavras[inst.add2.endPalavra];
                cpu->registrador3.atualizado = 1;
                printf("Subtracao -> RAM posicao %d com resultado %d (%d - %d)\n", inst.add3.endBloco, cpu->registrador3.palavras[inst.add3.endPalavra], cpu->registrador1.palavras[inst.add1.endPalavra],cpu->registrador2.palavras[inst.add2.endPalavra]);
                break;

            case 2:  // Multiplicação
                cpu->registrador3.palavras[inst.add3.endPalavra] =
                    cpu->registrador1.palavras[inst.add1.endPalavra] * cpu->registrador2.palavras[inst.add2.endPalavra];
                cpu->registrador3.atualizado = 1;
                printf("Multiplicacao -> RAM posicao %d com resultado %d (%d * %d)\n", inst.add3.endBloco, cpu->registrador3.palavras[inst.add3.endPalavra], cpu->registrador1.palavras[inst.add1.endPalavra],cpu->registrador2.palavras[inst.add2.endPalavra]);
                break;

            case 3:  // Divisão
                if (cpu->registrador2.palavras[inst.add2.endPalavra] != 0) {
                    cpu->registrador3.palavras[inst.add3.endPalavra] =
                        cpu->registrador1.palavras[inst.add1.endPalavra] / cpu->registrador2.palavras[inst.add2.endPalavra];
                    cpu->registrador3.atualizado = 1;
                    printf("Divisao -> RAM posicao %d com resultado %d (%d / %d)\n", inst.add3.endBloco, cpu->registrador3.palavras[inst.add3.endPalavra], cpu->registrador1.palavras[inst.add1.endPalavra],cpu->registrador2.palavras[inst.add2.endPalavra]);
                } else {
                    printf("Erro: divisao por zero\n");
                }
                break;

            default:
                printf("Opcode desconhecido: %d\n", cpu->opcode);
                break;
        }

        cpu->PC++;
    }

    // Resultados
    
    // HITS : vezes que a CPU encontrou os dados diretamente na cache de nível 1 (L1).
    // MISSES : vezes que a CPU não encontrou os dados na cache de nível 1, e precisou buscar em caches mais lentas ou na RAM.
    printf("Cache 1 - Hits: %d, Misses: %d\n", cpu->hitC1, cpu->missC1);

    //HITS : vezes, após um miss em L1, os dados foram encontrados na cache de nível 2 (L2).
    //MISSES : vezes, a CPU precisou continuar procurando na cache de nível 3 ou na RAM.
    printf("Cache 2 - Hits: %d, Misses: %d\n", cpu->hitC2, cpu->missC2);

    //HITS : vezes, após misses em L1 e L2, os dados foram encontrados na cache de nível 3 (L3).
    //MISSES : vezes, os dados precisaram ser buscados na memória RAM.
    printf("Cache 3 - Hits: %d, Misses: %d\n", cpu->hitC3, cpu->missC3);

    //Soma dos custos definidos para acessar os diferentes níveis de cache e a RAM.
    printf("Tempo total de execução: %d\n", cpu->tempoTotal);
    
    exit(0);
}

void liberarCPU(CPU *cpu) {
    free(cpu->cache1);
    free(cpu->cache2);
    free(cpu->cache3);
    free(cpu);
}
