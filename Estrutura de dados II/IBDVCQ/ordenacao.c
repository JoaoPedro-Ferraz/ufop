#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "ordenacao.h"


static int particiona(Aluno *v, int p, int r, int *);
void troca(Aluno *a, Aluno *b);

void troca(Aluno *a, Aluno *b) {
    Aluno temp = *a;
    *a = *b;
    *b = temp;
}

void quickSort(Aluno *v, int tam, int *comparacoes) {
    quickRec(v, 0, tam - 1, comparacoes);
}

void quickRec(Aluno *v, int p, int r, int *comparacoes) {
    if (p >= r) 
        return;
    int q = particiona(v, p, r, comparacoes);
    quickRec(v, p, q - 1, comparacoes);
    quickRec(v, q + 1, r, comparacoes);
}

static int particiona(Aluno *v, int p, int r, int *comparacoes) {
    
    float nota_pivo = v[r].nota;
    int i = p - 1;

    for (int j = p; j < r; j++) {
        (*comparacoes)++;
        
        if (v[j].nota <= nota_pivo) {
            i++;
            if (i != j) {
                troca(&v[i], &v[j]);
            }
        }
    }
    
    
    i++;
    if (i != r) {
        troca(&v[i], &v[r]);
    }
    return i;
}