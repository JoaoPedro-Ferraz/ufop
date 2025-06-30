#include <stdlib.h>
#include <stdio.h>

#include "fila.h"

typedef struct cell{
    struct cell *prox;
    Item item;
}Celula;

struct fila {
    Celula *pPrimeiro, *pUltimo;
      int tam;
};

Fila *criarFila() {
    Fila *fila = malloc(sizeof(Fila));
    if(fila == NULL)
        return NULL;
    fila->pPrimeiro = NULL;
    fila->tam = 0;
    return fila;
}

bool filaEhVazia(Fila *fila) {
    return fila->tam == 0;
}

bool adicionarFila(Fila *fila, Item item) {
   Celula *nova = malloc(sizeof(Celula));
   if(nova == NULL)
        return false;
    nova->item = item;
    nova->prox = NULL;
    if(filaEhVazia(fila))
        fila->pPrimeiro = nova;
    else    
        fila->pUltimo->prox = nova;
    fila->pUltimo = nova;
    fila->tam++;
    return true;
}

bool removerFila(Fila *fila) {
    if(filaEhVazia(fila))
        return false;
    if(fila->tam == 1) {
        free(fila->pPrimeiro);
        fila->pPrimeiro = NULL;
        fila->pUltimo = NULL;
        fila->tam--;
        return true;
    }
    Celula *aux = fila->pPrimeiro;
    fila->pPrimeiro = aux->prox;
    free(aux);
    fila->tam--;
    return true;
}

bool destroyFila(Fila *fila) {
    while(!filaEhVazia(fila))
        removerFila(fila);
    free(fila);
    return true;
}


void imprimirFila(Fila *fila) {
    Celula *aux = fila->pPrimeiro;
    while(aux) {
        printf("([%d | %s])\n", aux->item.chave, aux->item.nome);
        aux = aux->prox;
    }
}
