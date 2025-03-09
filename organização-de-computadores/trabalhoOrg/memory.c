#include "memory.h"
#include <stdlib.h>
#include <time.h>

sMemory* criaMemory() {
    sMemory* memory = malloc(sizeof(sMemory));
    if(memory ==NULL) 
        return NULL;

    memory->comandos = malloc(NUM_COM *sizeof(sComandoOp));
    if(memory->comandos == NULL)
        free(memory);

    return memory;
}
 
void startMemory(sMemory* memory) {
    srand(time(NULL));
    for(int i = 0; i < TAM_RAM; i++) {
        memory->ram[i] = rand() % 100 + 1;
    }
}

int getMemory(sMemory* memory, int endereco) {
    return memory->ram[endereco];
}

void setMemory(sMemory* memory, int resultado, int i) {
    memory->ram[memory->comandos[i].endereco3] = resultado;
}