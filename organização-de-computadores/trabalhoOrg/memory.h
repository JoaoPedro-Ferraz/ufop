#ifndef MEMORY_H
#define MEMORY_H
//numero de comandos
#define TAM_COM 3
#define NUM_COM 8 * TAM_COM
//tamanho da Ram
#define TAM_RAM 20

typedef struct {
    int opCode;
    int endereco1;
    int endereco2;
    int endereco3;
}sComandoOp;

typedef struct {
    int ram [TAM_RAM];
    sComandoOp* comandos;
}sMemory;

//aloca structs
sMemory* criaMemory();
//inicia Ram
void startMemory(sMemory*);
//get Ram para registradores
int getMemory(sMemory*, int);
//set Registradores para Ram
void setMemory(sMemory*, int, int);
 
#endif // MEMORY_H