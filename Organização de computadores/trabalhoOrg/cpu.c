#include "cpu.h"
#include <stdlib.h>
#include <stdio.h>
//-1 encerra
//0 get ou vazio
//1 set
//2 soma
//3 sub
//4 multiplicacao
//5 divisao
//5 fatorial
//7 fibonacci
//8 mmc
//9 mdc

//Alocando registradores
sRegistradores* criaRegistradores() {
    sRegistradores* registradores = malloc(sizeof(sRegistradores));
    if(registradores == NULL) {
        printf("Erro ao alocar registradores\n");
        return 0;
    }
    return registradores;
}

int somaProcessador(int registrador1, int registrador2) {
    return registrador1 + registrador2;
}

int subtracaoProcessador(int registrador1, int registrador2) {
    return registrador1 - registrador2;
}

int multiplicacaoProcessador(int registrador1, int registrador2) {
    int resultado = 0;
    for(int i = 0; i < registrador2; i++) {
        resultado = somaProcessador(resultado,registrador1);
    }
    return resultado;
}

int divisaoProcessador(int registrador1, int registrador2) {
    if (registrador2 == 0) {
        printf("Erro: Divisão por zero\n");
        return -1;
    }
    if (registrador1 < registrador2) {
        return 0;
    }
    return 1 + divisaoProcessador(registrador1 - registrador2, registrador2);
}

int fatorialProcessador(int registrador1) {
    int resultado = 1;

    for(int i = registrador1; i > 1; i--) {
        resultado = multiplicacaoProcessador(resultado, i);
    }

    return resultado;
}

int fibonacciProcessador(int registrador1) {
    if (registrador1 == 0) {
        return 0;
    } else if (registrador1 == 1) {
        return 1;
    }

    int a = 0; // F(0)
    int b = 1; // F(1)
    int temp = 0;

    for (int i = 2; i <= registrador1; i++) {
        temp = somaProcessador(a,b);
        a = b;
        b = temp;
    }

    return b;
}

int mdcProcessador(int registrador1, int registrador2) {
    while (registrador1 != registrador2) {
        if (registrador1 > registrador2) {
            registrador1 = subtracaoProcessador(registrador1, registrador2);
        } else {
            registrador2 = subtracaoProcessador(registrador2, registrador1);
        }
    }
    return registrador1;
}

int mmcProcessador(int registrador1, int registrador2) {

    int maior = registrador1 > registrador2 ? registrador1 : registrador2;
    int menor = registrador1 < registrador2 ? registrador1 : registrador2; 
    int multiplo = maior;

    while (multiplo % menor != 0) {
        multiplo = somaProcessador(multiplo, maior);
    }

    return multiplo;
}