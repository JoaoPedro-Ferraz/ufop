#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
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

void mergeSort(int *v, int tam) {
    mergeRec(v, 0, tam - 1);
}

void mergeRec(int *v, int esq, int dir) {
    if(esq == dir)
        return;
    int meio = (esq + dir) / 2;
    mergeRec(v, esq, meio);
    mergeRec(v, meio+1, dir);
    merge(v, esq, meio, dir);
}

void merge(int *v, int esq, int meio, int dir) {
    int tamEsq = meio - esq + 1;
    int tamDir = dir - meio;
    int *vEsq = malloc(tamEsq * sizeof(int));
    int *vDir = malloc(tamDir * sizeof(int));
    for(int i = 0; i < tamEsq; i++)
        vEsq[i] = v[i + esq];
    for(int j = 0; j < tamDir; j++)
        vDir[j] = v[meio+j+1]; 
    int i = 0, j = 0;
    for(int k = esq; k <= dir; k++) {
        if(i == tamEsq) 
            v[k] = vDir[j++];
        else if(j == tamDir)
            v[k] = vEsq[i++];
        else if(vEsq[i] <= vDir[j])
            v[k] = vEsq[i++];
        else 
            v[k] = vDir[j++];
    }
    free(vEsq);
    free(vDir);
}

void quickSort(int *v, int tam) {
    quickRec(v, 0, tam -1);
}

void quickRec(int *v, int p, int r) {
    if(p > r)
        return ;
    int q = quick(v, p, r);
    quickRec(v, p, q-1);
    quickRec(v, q+1, r);
}

int quick(int *v, int p, int r) {
    int x = v[r];
    int i = p -1;
    int comp = 0, mov = 0;
    for(int j = p; j < r; j++) {
        comp++;
        if(v[j] <= x) {
            mov++;
            troca(&v[++i], &v[j]);
        }
    }
    mov++;
    troca(&v[i+1], &v[r]);
    printf("([mov : %d] [comp : %d])\n", mov, comp);
    return i+1;
}

void heapRefaz(int *v, int esq, int dir) {
    int i = esq, aux = v[i];
    int j = i * 2 + 1;
    while(j <= dir) {
        if(j < dir && v[j] < v[j+1])
            j = j + 1;
        if(aux >= v[j])
            break;
        v[i] = v[j];
        i = j;
        j = i * 2 + 1;
    }
}

void heapConstroi(int *v, int tam) {
    int esq = (tam / 2) - 1;
    while(esq >= 0) {
        heapRefaz(v, esq, tam-1);
        esq--;
    }
}