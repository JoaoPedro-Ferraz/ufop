#include "pilha.h"
#include <stdio.h>

int main() {
    Pilha *pilha = criarPilha();
    Item item = {"ab)(c"};
    if(valida_parenteses(item.sequencia, 5, pilha))
        printf("Valido\n");
    else 
        printf("Invalido\n");
    destroyPilha(pilha);
    return 0;
}