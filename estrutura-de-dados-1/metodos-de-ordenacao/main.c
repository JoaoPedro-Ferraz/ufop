#include <stdio.h>
#include "metodosDeOrdenacao.h"

int main() {
    int vetor[10] = { 7, 9, 5, 3, 6, 8, 8, 3, 0, 1};
    insertionSort(vetor, 10);
    for(int i = 0; i < 10; i++) {
        printf(" %d ", vetor[i]);
    }
    return 0;
}