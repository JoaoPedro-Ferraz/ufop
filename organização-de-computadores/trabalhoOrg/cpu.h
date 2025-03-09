#ifndef CPU_H
#define CPU_H

typedef struct {
    int registrador1;
    int registrador2;
    int resultado;
}sRegistradores;

//alocacao registradores
sRegistradores* criaRegistradores();
int somaProcessador(int, int);
int subtracaoProcessador(int, int);
int multiplicacaoProcessador(int, int);
int divisaoProcessador(int, int);
int fatorialProcessador(int);
int fibonacciProcessador(int);
int mdcProcessador(int, int);
int mmcProcessador(int,int);

#endif //CPU_H