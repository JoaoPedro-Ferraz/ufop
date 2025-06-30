#include <stdio.h>

#include "fila.h"

void testarFila();

int main() {
    testarFila();
    return 0;
}

void testarFila() {
    Fila *fila = criarFila();
    printf("Fila eh vazia : %s\n", filaEhVazia(fila) ? "SIM" : "NAO");
    printf("Inseriu : %s\n", adicionarFila(fila, (Item){1, "Joao"}) ? "SIM" : "NAO");
    printf("Inseriu : %s\n", adicionarFila(fila, (Item){2, "Pedro"}) ? "SIM" : "NAO");
    printf("Removeu : %s\n", removerFila(fila) ? "SIM" : "NAO");
    printf("Removeu : %s\n", removerFila(fila) ? "SIM" : "NAO");
    printf("Inseriu : %s\n", adicionarFila(fila, (Item){1, "Joao"}) ? "SIM" : "NAO");
    printf("Inseriu : %s\n", adicionarFila(fila, (Item){2, "Pedro"}) ? "SIM" : "NAO");
    imprimirFila(fila);
    destroyFila(fila);
    printf("Fila eh vazia : %s\n", filaEhVazia(fila) ? "SIM" : "NAO");
}