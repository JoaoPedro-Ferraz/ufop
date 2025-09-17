#ifndef REGISTRO_H
#define REGISTRO_H

#define M 2
#define MM (2 * M)

typedef long TipoChave;

typedef struct TipoRegistro {
    TipoChave Chave;
    long dado1;
    char dado2[1000];
    char dado3[5000];
} TipoRegistro;

#endif