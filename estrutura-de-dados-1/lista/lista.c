#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

typedef struct cell {
    struct cell *prox;
    Item item;
}Celula;

struct lista {
    Celula *pPrimeiro;
    Celula *pUltimo;
    int tam;
};

bool listaEhVazia(Lista *lista) {
    return lista->tam == 0;
}
Lista *criarLista() {
    Lista *criarLista = malloc(sizeof(Lista));
    if(criarLista == NULL)
        return NULL;
    criarLista->pPrimeiro = NULL;
    criarLista->pUltimo = NULL;
    criarLista->tam = 0;
    return criarLista;
}

bool inserirInicio(Lista *lista, Item item) {
   Celula *novoNo = malloc(sizeof(Celula));
   if(novoNo == NULL)
        return false;
    novoNo->item = item;
    novoNo->prox = lista->pPrimeiro;
    lista->pPrimeiro = novoNo;
    if(lista->tam == 0)
        lista->pUltimo = novoNo;    
    lista->tam++;
}

bool inserirMeio(Lista *lista, Item item, int pos) {
    if(listaEhVazia(lista)) {
        inserirInicio(lista, item);
        return true;
    }
    if(lista->tam == pos){
        inserirFim(lista, item);
        return true;
    }
    Celula *aux = lista->pPrimeiro;
    for(int i = 0; i < pos -1; i ++) 
        aux = aux->prox;
    Celula *novaCelula = malloc(sizeof(Celula));
    if(novaCelula == NULL)
        return false;
    novaCelula->prox = aux->prox;
    aux->prox = novaCelula;
    novaCelula->item = item;
    lista->tam++;
    return true;
}

bool inserirFim(Lista *lista, Item item) {
    if(listaEhVazia(lista)) {
        inserirInicio(lista, item);
        return true;
    }
    Celula *novaCelula = malloc(sizeof(Celula));
    if(novaCelula == NULL)
        return false;
    novaCelula->prox = NULL;
    lista->pUltimo->prox = novaCelula;
    lista->pUltimo = novaCelula;
    novaCelula->item = item;
    lista->tam++;
}

bool removerInicio(Lista *lista) {
    if(listaEhVazia(lista))
        return false;
    if(lista->tam == 1) {
        free(lista->pPrimeiro);
        lista->pPrimeiro = NULL;
        lista->pUltimo = NULL;
        lista->tam--;
        return true;
    }
    Celula *aux = lista->pPrimeiro;
    lista->pPrimeiro = aux->prox;
    free(aux);
    lista->tam--;
    return true;
}

bool removerMeio(Lista *lista, int pos) {
    if(listaEhVazia(lista))
        return false;
    if(pos == 0) {
        removerInicio(lista);
        return true;
    }
    if(pos  == lista->tam - 1) {
        removerFim(lista);
        return true;
    }
    Celula *aux = lista->pPrimeiro;
    for(int i = 0; i < pos -1; i ++) 
        aux = aux->prox;
    Celula *remove = aux->prox;
    aux->prox = remove->prox;
    free(remove);
    lista->tam--;
}

bool removerFim(Lista *lista) {
    if(listaEhVazia)
        return false;
    if(lista->tam == 1) {
        removerInicio(lista);
        return true;
    }
    Celula *aux = lista->pPrimeiro;
    while(aux->prox != lista->pUltimo)
        aux = aux->prox;
    free(lista->pUltimo);
    lista->pUltimo = aux;
    aux->prox = NULL;
    lista->tam--;
    return true;
}

void imprimirLista(Lista *lista) {
    Celula *aux = lista->pPrimeiro;
    while(aux != NULL) {
        printf("ITEM -> [%d]\n", aux->item);
        aux = aux->prox;
    }
}

void listaDestroy(Lista *lista) {
    while(lista->tam != 0) 
        removerInicio(lista);
    
}

void imprime_texto_chave_maior_que(Lista *lista, int a, int b) {
    Celula *aux = lista->pPrimeiro;
    while(aux != NULL) {
        if(aux->item.chave >= a && aux->item.chave <= b) 
            printf("%s\n", aux->item.posicao);
        aux = aux->prox;
    }
}