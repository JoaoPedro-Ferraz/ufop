#include "metodosDeOrdenacao.h"

void troca(int *num1, int *num2) {
    int aux = *num1;
    *num1 = *num2;
    *num2 = aux;
}

void bubbleSort(int *vetor, int tam) {
    for(int i = 0; i < tam; i++) {
        for(int j = 1; j < tam - i; j++) {
            if(vetor[j] < vetor[j - 1])
                troca(&vetor[j], &vetor[j - 1]);
        }
    }
}

void selectionSort(int *vetor, int tam) {
    for(int i = 0; i < tam; i++) {
        int min = i;
        for(int j = i + 1; j < tam; j++) {
            if(vetor[j] < vetor[min])
                min = j;
        }
        troca(&vetor[i], &vetor[min]);
    }
}

void insertionSort(int *vetor, int tam) {
    for(int i = 1; i < tam; i++) {
        int aux = vetor[i];
        int j = i - 1;
        while(j >= 0 && aux < vetor[j]) {
            vetor[j + 1] = vetor[j];
            j = j - 1;
        }
        troca(&vetor[j + 1], &aux);
    }
}