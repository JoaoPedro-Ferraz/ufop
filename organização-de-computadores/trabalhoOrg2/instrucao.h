#ifndef INSTRUCAO_H
#define INSTRUCAO_H

typedef struct {
    int endBloco;
    int endPalavra;
} Endereco;

typedef struct {
    Endereco add1;
    Endereco add2;
    Endereco add3;
    int opcode;
} Instrucao;

#endif
