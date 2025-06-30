#include <stdio.h>

void printSoma(int registrador1, int registrador2, int resultado) {
    printf("%d soma %d resultado: %d\n", 
    registrador1,registrador2,resultado);
}

void printsubtracao(int registrador1, int registrador2, int resultado) {
    printf("%d subtracao %d resultado: %d\n", 
    registrador1,registrador2,resultado);
}
 
void printMultiplicacao(int registrador1, int registrador2, int resultado) {
    printf("%d multiplicacao %d resultado: %d\n", 
    registrador1,registrador2,resultado);
}

void printDivisao(int registrador1, int registrador2, int resultado) {
    printf("%d divisao %d resultado: %d\n", 
    registrador1,registrador2,resultado);
}

void printFatorial(int registrador1, int resultado) {
    printf("%d fatorial resultado: %d\n", 
    registrador1,resultado);
}

void printFibonacci(int registrador1, int resultado) {
    printf("%d fibonacci resultado: %d\n", 
    registrador1,resultado);
}

void printfMdc (int registrador1, int registrador2, int resultado){
    printf("%d mdc %d resultado: %d\n",
    registrador1,registrador2,resultado);
}

void printSet(int endereco3, int resultado) {
    printf("%d set &%d\n", 
    endereco3, resultado);
    printf("--------------------------\n");
}

void printGet(int endereco1, int endereco2) {
    printf("get %d e %d\n", 
    endereco1, endereco2);
}