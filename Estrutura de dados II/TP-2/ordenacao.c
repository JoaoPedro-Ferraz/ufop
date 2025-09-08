#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "ordenacao.h"

// Declaração antecipada das funções
static int particiona(Aluno *v, int p, int r);
void troca(Aluno *a, Aluno *b);

void troca(Aluno *a, Aluno *b) {
    Aluno temp = *a;
    *a = *b;
    *b = temp;
}

void quickSort(Aluno *v, int tam) {
    quickRec(v, 0, tam - 1);
}

void quickRec(Aluno *v, int p, int r) {
    if (p >= r) 
        return;
    int q = particiona(v, p, r);
    quickRec(v, p, q - 1);
    quickRec(v, q + 1, r);
}

static int particiona(Aluno *v, int p, int r) {
    // Pivô é o último elemento
    float nota_pivo = v[r].nota;
    int i = p - 1;

    for (int j = p; j < r; j++) {
        // Ordena por nota (decrescente: maiores notas primeiro)
        if (v[j].nota <= nota_pivo) {
            i++;
            if (i != j) {
                troca(&v[i], &v[j]);
            }
        }
    }
    
    // Coloca o pivô na posição correta
    i++;
    if (i != r) {
        troca(&v[i], &v[r]);
    }
    return i;
}