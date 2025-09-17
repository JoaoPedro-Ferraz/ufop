#ifndef HEAP_H
#define HEAP_H

#include "leituraArquivoSB.h"


typedef struct {
    Aluno dado;
    int ativo; 
} HeapItem;


int cmpAlunoRunSB(const Aluno *a, const Aluno *b);


int cmpHeap(const HeapItem *a, const HeapItem *b);


void heapify(HeapItem *heap, int n, int i);


void constroiHeap(HeapItem *heap, int n);

#endif 
