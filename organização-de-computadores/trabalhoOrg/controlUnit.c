#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "cpu.h"
#include "memory.h"
#include "print.h"

bool leituraArquivo(char * argv, sMemory *memory);
void decodificaComando(sMemory*, sRegistradores*);
void printMemory(sMemory*);

int main(int argc, char *argv[]) {
    //verificando entrada de dados
    if(argc <= 1){
        printf("Insira um arquivo\n");
        return 0;
    }

    //iniciando "memory"
    sMemory* memory = criaMemory();
    //preenchendo "RAM"
    startMemory(memory);
    //iniciando "Registradores"
    sRegistradores* pRegistradores = criaRegistradores();

    //lendo comandos arquivo
    if(!leituraArquivo(argv[1], memory)) {
        printf("Nao foi possivel abrir o arquivo\n");
        return 0;
    }

    decodificaComando(memory, pRegistradores);
    //Liberando Memoria
    free(memory->comandos);
    free(memory);
    free(pRegistradores);
    return 0;
}

void decodificaComando(sMemory* memory, sRegistradores* pRegistradores) {
    int i = 0;
    //print linha separacao
    printf("--------------------------\n");
    do{
        switch(memory->comandos[i].opCode){
        case -1:
            printf("Programa encerrado!\n");
            return;
        case 0:
            pRegistradores->registrador1 = getMemory(memory, memory->comandos[i].endereco1);
            pRegistradores->registrador2 = getMemory(memory, memory->comandos[i].endereco2);
            printGet( pRegistradores->registrador1,  pRegistradores->registrador2);
            break;
        case 1:
            setMemory(memory, pRegistradores->resultado, i);
            printSet(pRegistradores->resultado, memory->comandos[i].endereco3);
            break;
        case 2:
            pRegistradores->resultado = somaProcessador(
            pRegistradores->registrador1, pRegistradores->registrador2);
            printSoma(pRegistradores->registrador1,pRegistradores->registrador2,
            pRegistradores->resultado);
            break;
        case 3:
            pRegistradores->resultado = subtracaoProcessador(
            pRegistradores->registrador1, pRegistradores->registrador2);
            printsubtracao(pRegistradores->registrador1,pRegistradores->registrador2,
            pRegistradores->resultado);
            break;
        case 4:
            pRegistradores->resultado = multiplicacaoProcessador(
            pRegistradores->registrador1, pRegistradores->registrador2);
            printMultiplicacao(pRegistradores->registrador1,pRegistradores->registrador2,
            pRegistradores->resultado);
            break;
        case 5:
            pRegistradores->resultado = divisaoProcessador(
            pRegistradores->registrador1, pRegistradores->registrador2);
            printDivisao(pRegistradores->registrador1,pRegistradores->registrador2,
            pRegistradores->resultado);
            break;
        case 6:
            pRegistradores->resultado = fatorialProcessador(
            pRegistradores->registrador1);
            printFatorial(pRegistradores->registrador1,
            pRegistradores->resultado);
            break;
        case 7:
            pRegistradores->resultado = fibonacciProcessador(
            pRegistradores->registrador1);
            printFibonacci(pRegistradores->registrador1,
            pRegistradores->resultado);
            break;
        case 8:
            pRegistradores->resultado = mdcProcessador(
            pRegistradores->registrador1, pRegistradores->registrador2);
            printMdc(pRegistradores->registrador1,
            pRegistradores->resultado);
        case 9:
            pRegistradores->resultado = mmcProcessador(
            pRegistradores->registrador1, pRegistradores->registrador2);
            printMmc(pRegistradores->registrador1,
            pRegistradores->resultado);
        }
        i++;
    }
    while(i < NUM_COM);
}

bool leituraArquivo(char *argv, sMemory *memory) {
    FILE* file = fopen(argv, "r");
    if(file == NULL) {
        return false;
    }
    for(int i = 0; i < NUM_COM; i++) {
        fscanf(file, "%d%d%d%d", 
        &memory->comandos[i].opCode,
        &memory->comandos[i].endereco1,
        &memory->comandos[i].endereco2,
        &memory->comandos[i].endereco3);
    }

    fclose(file);
    return true;
}

void printMemory(sMemory* memory) {
    for(int i = 0; i < TAM_RAM; i++) {
        printf("%d", memory->ram[i]);
    }
}