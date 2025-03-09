#ifndef FILA_H
#define FILA_H

#include "item.h"
#include <stdbool.h>

typedef struct fila Fila;

Fila *criarFila();
bool filaEhVazia(Fila *);
bool adicionarFila(Fila *, Item);
bool removerFila(Fila *);
bool destroyFila(Fila *);
void imprimirFila(Fila *);
#endif //FILA_H