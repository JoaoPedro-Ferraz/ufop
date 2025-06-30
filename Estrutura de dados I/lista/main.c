#include "lista.h"
#include <stdio.h>

void testarListaPonteiro();
int main() {
    testarListaPonteiro();
    return 0;
}

void testarListaPonteiro() {
    Lista *lista = criarLista();
    inserirFim(lista, (Item){11, "Primeiro"});
    inserirFim(lista, (Item){15, "Segundo"});
    inserirFim(lista, (Item){21, "Terceiro"});
    imprime_texto_chave_maior_que(lista, 12, 20);
    listaDestroy(lista);
}