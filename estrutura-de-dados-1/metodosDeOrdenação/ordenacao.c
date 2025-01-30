#include <stdio.h>
#include <stdbool.h>
#include "ordenacao.h"

void buubleSort(int  *v, int n) { 
    int mov = 0, comp = 0;
    for(int i = 0; i < n; i++) {
        int movi = 0;
        for(int j = 1; j < n - i; j++) {
            comp++;
            if(v[j] < v[j-1]){
                troca(&v[j], &v[j-1]);
                movi++;
                mov++;
            }
        }
    if(movi == 0)
        break;
    }
    printf("([ Comp : %d | Mov : %d])\n", comp, mov);
}

void selectionSort(int  *v, int n) {
    int imenor;
    int comp = 0, mov = 0;
    for(int i = 0; i < n; i++) {
    bool ordenado = false;
        imenor = i;
        for(int j = i+1; j < n; j++) {
            comp++;
            if(v[j] < v[imenor]){
                imenor = j;
                mov++;
            }
        if(mov == 0)
            ordenado = true;
        }
    if(ordenado)
        break;
    troca(&v[i], &v[imenor]);
    }
    printf("([ Comp : %d | Mov : %d])\n", comp, mov);
}

void insertionSort(int  *v, int n) {
    int comp = 0; int mov = 0;
    for(int i = 1; i < n; i++) {
        int j = i - 1, aux = v[i];
        comp++;
        while(j >= 0 && v[j] > aux) {
            v[j+1] = v[j];
            j--;
            mov++;
        }
        mov++;
    v[j+1] = aux;
    }
    printf("([ Comp : %d | Mov : %d])\n", comp, mov);
}

void troca(int *a , int *b) {
    int aux = (*a);
    (*a) = (*b);
    (*b) = aux;
}