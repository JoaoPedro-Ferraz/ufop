#include <stdio.h>
#include <stdlib.h>

#include "fila.h"

#define MAX_TAM 5

struct fila {
    Item item[MAX_TAM];
    int inicio;
    int fim;
};

Fila *criarFila() {
    Fila *fila = malloc(sizeof(Fila));
    if(fila == NULL)
        return NULL;
    fila->inicio = 0;
    fila->fim = 0;
}

bool filaEhVazia(Fila *fila) {
    return fila
}

bool adicionarFila(Fila *fila, Item item) {
    return true;
}

bool removerFila(Fila *fila) {
    return true;
}

bool destroyFila(Fila *fila) {
    return true;
}

void imprimirFila(Fila *fila) {
    return true;
}
