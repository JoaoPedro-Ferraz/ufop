#ifndef LISTA_H
#define LISTA_H

#include <stdbool.h>
#include "item.h"

typedef struct lista Lista;

bool listaEhVazia(Lista *);
Lista *criarLista();
bool inserirInicio(Lista *, Item);
bool inserirMeio(Lista *, Item, int);
bool inserirFim(Lista *, Item);
bool removerInicio(Lista *);
bool removerMeio(Lista *, int);
bool removerFim(Lista *);
void imprimirLista(Lista *);
void listaDestroy(Lista *);
void imprime_texto_chave_maior_que(Lista *, int, int);
#endif //LISTA_H