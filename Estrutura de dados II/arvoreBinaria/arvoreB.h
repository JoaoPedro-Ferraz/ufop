#ifndef ARVOREB_H
#define ARVOREB_H

#include "registro.h"

#define M 2  // Grau minimo
#define MM (2*M) // Ordem da arvore (maximo de chaves)

typedef struct TipoPagina* TipoApontador;

// === Estrutura de uma pagina (no) da arvore B ===
typedef struct TipoPagina {
    short n;
    TipoRegistro r[MM];
    TipoApontador p[MM + 1];
} TipoPagina;
// Inicializa a arvore como vazia
void Inicializa(TipoApontador *Arvore);
// Realiza a busca de um registro pela chave
int Pesquisa(TipoRegistro *x, TipoApontador Ap, int *comparacoes);

void Imprime(TipoApontador Arvore);
// Insere um registro em uma pagina (mantem ordenacao)
void InsereNaPagina(TipoApontador Ap, TipoRegistro Reg, TipoApontador ApDir, int *comparacoes);
// Funcao recursiva principal de insercao
void Ins(TipoRegistro Reg, TipoApontador Ap, short *Cresceu,
         TipoRegistro *RegRetorno, TipoApontador *ApRetorno, int *comparacoes);
// Wrapper da insercao (chamada externa)
void Insere(TipoRegistro Reg, TipoApontador *Ap, int *comparacoes);
// Libera memoria da arvore
void Limpar(TipoApontador *Ap);

#endif