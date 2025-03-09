#ifndef PILHA_H
#define PILHA_H

#include <stdbool.h>
#include "item.h"

typedef struct cell{
    Item item;
    struct cell *prox;
}Celula;

typedef struct {
    Celula *pPrimeiro;
    int tam;
}Pilha;

Pilha *criarPilha();
bool pilhaEhVazia(Pilha *);
bool pilhaPop(Pilha *);
bool pilhaPush(Pilha *, Item);
void imprimirPilha(Pilha *);
bool destroyPilha(Pilha *);
bool valida_parenteses(char *, int, Pilha *);
#endif //PILHA_H