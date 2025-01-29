#include "pilha.h"
#include <stdlib.h>
#include <stdio.h>

Pilha *criarPilha() {
    Pilha *criarPilha = malloc(sizeof(Pilha));
    if(criarPilha == NULL)
        return NULL;
    criarPilha->tam = 0;
    criarPilha->pPrimeiro = NULL;
    return criarPilha;
}

bool pilhaEhVazia(Pilha *pilha) {
    return pilha->tam == 0;
}

bool pilhaPush(Pilha *pilha, Item item) {
    Celula *novaCelula = malloc(sizeof(Celula));
    if(novaCelula == NULL)
        return false;
    if(pilhaEhVazia(pilha)) {
        pilha->pPrimeiro = novaCelula;
        novaCelula->prox = NULL;
        novaCelula->item = item;
        pilha->tam++;
        return true;
    }
    novaCelula->prox = pilha->pPrimeiro;
    pilha->pPrimeiro = novaCelula;
    novaCelula->item = item;
    pilha->tam++;
    return true;
}

bool pilhaPop(Pilha *pilha) {
    if(pilhaEhVazia(pilha))
        return false;
    if(pilha->tam == 1) {
        free(pilha->pPrimeiro);
        pilha->pPrimeiro = NULL;
        pilha->tam--;
        return true;
    }
    Celula *aux = pilha->pPrimeiro;
    pilha->pPrimeiro = aux->prox;
    free(aux);
    pilha->tam--;
    return true;
}

void imprimirPilha(Pilha *pilha) {
    Celula *aux = pilha->pPrimeiro;
    while(aux != NULL){
        printf(" [%d] \n", aux->item);
        aux = aux->prox;
    }
}

bool destroyPilha(Pilha *pilha) {
    if(pilhaEhVazia(pilha))
        return false;
    while(pilha->tam != 0)
        pilhaPop(pilha);
    return true;
}

bool valida_parenteses(char *sequencia, int tam, Pilha *pilha) {
    Item item;
    for(int i = 0; i < tam; i ++) 
        if(sequencia[i] == '(')
            pilhaPush(pilha, item);
        else if(sequencia[i] == ')')   
            if(!pilhaEhVazia(pilha))
                pilhaPop(pilha);
    return pilhaEhVazia(pilha);
}