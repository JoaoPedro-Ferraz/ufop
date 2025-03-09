#include "lista.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX_TAM 10

struct lista {
    Item item[MAX_TAM];
    int tam;
};

bool listaEhVazia(Lista *lista) {
    return lista->tam == 0;
}

Lista *criarLista() {
    Lista *criarLista = malloc(sizeof(Lista));
    if(criarLista == NULL)
        return NULL;
    criarLista->tam = 0;
    return criarLista;
}

bool inserirInicio(Lista *lista, Item item) {
    if(lista->tam == MAX_TAM)
        return false;
    for(int i = lista->tam - 1; i >= 0; i--)  // Correção aqui
        lista->item[i + 1] = lista->item[i];
    lista->item[0] = item;
    lista->tam++;
    return true;
}

bool inserirMeio(Lista *lista, Item item, int pos) {
    if(lista->tam == MAX_TAM)
        return false;
    for(int i = lista->tam - 1; i >= pos; i--)  // Correção aqui
        lista->item[i + 1] = lista->item[i];
    lista->item[pos] = item;  // Correção aqui
    lista->tam++;
    return true;
}

bool inserirFim(Lista *lista, Item item) {
    if(lista->tam == MAX_TAM)
        return false;
    lista->item[lista->tam] = item;  // Correção aqui
    lista->tam++;
    return true;
}

bool removerInicio(Lista *lista) {
    if(listaEhVazia(lista))
        return false;
    for(int i = 0; i < lista->tam - 1; i++)
        lista->item[i] = lista->item[i + 1];
    lista->tam--;
    return true;
}

bool removerMeio(Lista *lista, int pos) {
    if(pos < 0 || pos >= lista->tam)
        return false;  // Garantir que a posição seja válida
    for(int i = pos; i < lista->tam - 1; i++)
        lista->item[i] = lista->item[i + 1];
    lista->tam--;
    return true;
}

bool removerFim(Lista *lista) {
    if(listaEhVazia(lista))
        return false;
    lista->tam--;
    return true;
}

void imprimirLista(Lista *lista) {
    for(int i = 0; i < lista->tam; i++) {
        printf("[%d]\n", lista->item[i]);
    }
}

void listaDestroy(Lista *lista) {
    free(lista);
}
 