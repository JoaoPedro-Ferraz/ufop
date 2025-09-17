#include <stdio.h>
#include <stdlib.h>
#include "arvoreB.h"

void Inicializa(TipoApontador *Arvore) {
    *Arvore = NULL;
}

int Pesquisa(TipoRegistro *x, TipoApontador Ap, int *comparacoes) {
    long i = 1;

    if (Ap == NULL) {
        printf("TipoRegistro nao esta presente\n");
        return 0;
    }
    // Avanca ate encontrar posicao potencial da chave
    while (i < Ap->n && x->Chave > Ap->r[i - 1].Chave) {
        i++;
        if (comparacoes) (*comparacoes)++;
    }
    if (comparacoes) (*comparacoes)++;
    // Verifica se a chave foi encontrada
    if (x->Chave == Ap->r[i - 1].Chave) {
        *x = Ap->r[i - 1];
        return 1;
    }
    // Continua a busca na subarvore apropriada
    if (x->Chave < Ap->r[i - 1].Chave) {
        return Pesquisa(x, Ap->p[i - 1], comparacoes);
    } else {
        return Pesquisa(x, Ap->p[i], comparacoes);
    }
}
// Imprime a arvore em ordem (in-order traversal) - nao necessaria pro codigo
void Imprime(TipoApontador Arvore) {
// funcao if: implementa parte do algoritmo; descricao breve sem acentos

    if (Arvore != NULL) {
        int i;
        
        for (i = 0; i < Arvore->n; i++) {
            Imprime(Arvore->p[i]);
            printf("%ld ", Arvore->r[i].Chave);
        }
        Imprime(Arvore->p[i]);
    }
}

// Insere um registro em uma pagina, mantendo ordenacao
void InsereNaPagina(TipoApontador Ap, TipoRegistro Reg, TipoApontador ApDir, int *comparacoes) {
    short NaoAchouPosicao = (Ap->n > 0);
    int k = Ap->n;

    while (NaoAchouPosicao) {
        if (comparacoes) (*comparacoes)++;

        if (Reg.Chave >= Ap->r[k - 1].Chave) {
            NaoAchouPosicao = 0;
        } else {
            Ap->r[k] = Ap->r[k - 1];
            Ap->p[k + 1] = Ap->p[k];
            k--;
            if (k < 1) NaoAchouPosicao = 0;
        }
    }

    Ap->r[k] = Reg;
    Ap->p[k + 1] = ApDir;
    Ap->n++;
}

// Funcao recursiva que trata a insercao e divisoes de pagina
void Ins(TipoRegistro Reg, TipoApontador Ap, short *Cresceu,
         TipoRegistro *RegRetorno, TipoApontador *ApRetorno, int *comparacoes) {

    long i = 1, j;
    TipoApontador ApTemp;

    if (Ap == NULL) { // Caso base: inserir em pagina nova (criacao de nova raiz futura)
        *Cresceu = 1;
        *RegRetorno = Reg;
        *ApRetorno = NULL;
        return;
    }
    // Busca posicao para insercao
    while (i < Ap->n && Reg.Chave > Ap->r[i - 1].Chave) {
        if (comparacoes) (*comparacoes)++;
        i++;
    }
    if (comparacoes) (*comparacoes)++;

    if (Reg.Chave == Ap->r[i - 1].Chave) {  // Registro duplicado
        printf("Erro: registro %ld ja esta presente\n", Reg.Chave);
        *Cresceu = 0;
        return;
    }

    if (Reg.Chave < Ap->r[i - 1].Chave) i--;  // Determina o filho correto para continuar insercao

    Ins(Reg, Ap->p[i], Cresceu, RegRetorno, ApRetorno, comparacoes); // Chamada recursiva para subarvore

    if (!*Cresceu) return;

    if (Ap->n < MM) { // Caso nao houve estouro, insere normalmente
        InsereNaPagina(Ap, *RegRetorno, *ApRetorno, comparacoes);
        *Cresceu = 0;
        return;
    }

    ApTemp = (TipoApontador) malloc(sizeof(TipoPagina)); // Caso pagina cheia: dividir pagina
    ApTemp->n = 0;
    ApTemp->p[0] = NULL;

    if (i < M + 1) {  // Se nova chave vai ficar na metade esquerda
        InsereNaPagina(ApTemp, Ap->r[MM - 1], Ap->p[MM], comparacoes); 
        Ap->n--;
        InsereNaPagina(Ap, *RegRetorno, *ApRetorno, comparacoes);
    } else {
        InsereNaPagina(ApTemp, *RegRetorno, *ApRetorno, comparacoes); // Se nova chave vai ficar na metade direita
    }
    // Move metade superior para nova pagina
    for (j = M + 2; j <= MM; j++) {
        InsereNaPagina(ApTemp, Ap->r[j - 1], Ap->p[j], comparacoes);
    }
    // Atualiza a pagina original com metade inferior
    Ap->n = M;
    ApTemp->p[0] = Ap->p[M + 1];
    *RegRetorno = Ap->r[M];
    *ApRetorno = ApTemp;
}

void Insere(TipoRegistro Reg, TipoApontador *Ap, int *comparacoes) {
    short Cresceu;
    TipoRegistro RegRetorno;
    TipoApontador ApRetorno, ApTemp;

    Ins(Reg, *Ap, &Cresceu, &RegRetorno, &ApRetorno, comparacoes);

    if (Cresceu) {
        ApTemp = (TipoApontador) malloc(sizeof(TipoPagina));
        ApTemp->n = 1;
        ApTemp->r[0] = RegRetorno;
        ApTemp->p[1] = ApRetorno;
        ApTemp->p[0] = *Ap;
        *Ap = ApTemp;
    }
}

void Limpar(TipoApontador *Ap) {
    if (*Ap != NULL) {
        for (int i = 0; i <= (*Ap)->n; i++) {
            Limpar(&(*Ap)->p[i]);
        }
        free(*Ap);
        *Ap = NULL;
    }
}