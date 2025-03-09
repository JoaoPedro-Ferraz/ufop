#ifndef ORDENACAO_H
#define ORDENACAO_H

void buubleSort(int  *, int);
void insertionSort(int  *, int);
void selectionSort(int  *, int);
void troca(int *, int *);
void mergeSort(int *, int);
void mergeRec(int *, int, int);
void merge(int *, int, int, int);
void quickSort(int *, int);
void quickRec(int *, int, int);
int quick(int *, int, int);
void heapConstroi(int *, int);
void heapRefaz(int *, int , int);

#endif //ORDENACAO_H