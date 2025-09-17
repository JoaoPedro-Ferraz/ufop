#include <string.h>
#include "heap.h"

extern long long comparacoes;

int cmpAlunoRunSB(const Aluno *a, const Aluno *b) {
    comparacoes++;
    if (a->nota < b->nota) return -1;
    if (a->nota > b->nota) return 1;
    return strcmp(a->inscricao, b->inscricao);
}

int cmpHeap(const HeapItem *a, const HeapItem *b) {
    return cmpAlunoRunSB(&a->dado, &b->dado);
}

void heapify(HeapItem *heap, int n, int i) {
    int menor = i;
    int esq = 2*i + 1;
    int dir = 2*i + 2;

    if (esq < n && cmpHeap(&heap[esq], &heap[menor]) < 0) menor = esq;
    if (dir < n && cmpHeap(&heap[dir], &heap[menor]) < 0) menor = dir;

    if (menor != i) {
        HeapItem tmp = heap[i];
        heap[i] = heap[menor];
        heap[menor] = tmp;
        heapify(heap, n, menor);
    }
}

void constroiHeap(HeapItem *heap, int n) {
    for (int i = n/2 - 1; i >= 0; i--) {
        heapify(heap, n, i);
    }
}